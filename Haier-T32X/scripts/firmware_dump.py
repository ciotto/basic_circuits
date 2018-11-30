import telnetlib
import argparse
from subprocess import call
import sys
import tempfile

if hasattr(__builtins__, 'raw_input'):
	input=raw_input


def print_progress(message):
	sys.stdout.write('%s\r' % message)
	sys.stdout.flush()


class Client:
	REGISTERS = [
		'r0',
		'r1',
		'r2',
		'r3',
		'r4',
		'r5',
		'r6',
		'r7',
		'r8',
		'r9',
		'r10',
		'r11',
		'r12',
		'sp',
	]

	def __init__(self, host, port, no_input=False):
		self.tn = telnetlib.Telnet(host, port)
		self.tn.read_until('> ')
		self.no_input = no_input

	def send_cmq(self, cmd=''):
		"""Send generic command"""
		self.tn.read_eager()
		self.tn.write('%s\n' % cmd)
		return self.tn.read_until('> ')

	def send_reset(self):
		"""Send 'reset halt' command"""
		return self.send_cmq('reset halt')

	def parse_reg(self, string):
		"""Parse the 'reg name' output"""
		a = string.splitlines()[1].split(' ')
		return {
			'name': a[0],
			'size': a[1][2:-2],
			'value': int(a[2], 16),
		}

	def set_reg(self, name, value=0):
		"""Send 'reg name value' command"""
		return self.send_cmq('reg %s %s' % (name, value))

	def set_regs(self, names, value=0):
		"""Set multiple registers"""
		for name in names:
			self.set_reg(name, value)

	def set_pc(self, value=0):
		"""Set the PC register"""
		return self.set_reg('pc', value)

	def get_reg(self, name):
		"""Send 'get name' command"""
		while True:
			try:
				return self.parse_reg(self.send_cmq('reg %s' % name))
			except Exception as e:
				print('\nParse error: %s' % e)
				if not self.no_input:
					input('Press a key to continue: ')

	def get_regs(self, names):
		"""Get multiple registers"""
		for name in names:
			yield self.get_reg(name)

	def step(self):
		"""Send 'step' command"""
		return self.send_cmq('step')

	def read_step(self, address, value=0):
		"""Send 'reset halt', set PC to 'address', set general purpose registers to 'value' and do step"""
		self.send_reset()
		self.set_pc(address)
		self.set_regs(self.REGISTERS, value)
		self.step()


def search(args):
	"""Search for an operation that read the memory"""
	print('Search command..')

	def _get_changed(value=0):
		changed = []
		for r in c.get_regs(Client.REGISTERS[:-1]):
			if r['value'] != value:
				changed.append(r)
		return changed

	def _input_address(message):
		while True:
			user_input = input('%s: ' % message)

			if user_input.upper() in ['C', 'E']:
				return user_input.upper()

			try:
				user_input = int(user_input, 0)
				return user_input
			except ValueError as e:
				print(e)

	def _print_changed(changed, value):
		print('With value %s' % hex(value))
		for c in changed:
			print('%s (/%s): %s (%s)' % (c['name'].rjust(5), c['size'], hex(c['value']), c['value']))

	c = Client(args.host, args.port, no_input=args.no_input)

	address = args.address
	while True:
		print_progress('Try with address %s' % hex(address))

		c.read_step(address)
		changed1 = _get_changed()

		# There are a change in the registers?
		if changed1:
			c.read_step(address, 4)
			changed2 = _get_changed(4)

			# The register changes are differt?
			if any(x != y for x, y in zip(changed1, changed2)):
				# The difference between the changes is different to 4?
				if len(changed1) != 1 or len(changed2) != 1 or (
					abs(changed1[0]['value'] - changed2[0]['value']) != 4 and
					abs(changed1[0]['value'] - changed2[0]['value']) != 4294967292):
					print('\nPotentially usable address found:')
					_print_changed(changed1, 0)
					_print_changed(changed2, 4)

					if not args.no_input:
						i = None
						while i != 'C':
							i = _input_address('Insert a register value to retry, "C" to continue or "E" to exit')
							if i == 'C':
								continue
							elif i == 'E':
								exit()
							c.read_step(address, i)
							_print_changed(_get_changed(i), i)
				else:
					print('\nSkip sum operation')

		address += 2


def dump(args):
	"""Dump the firmware (not tested)"""
	print('Dump firmware..')

	c = Client(args.host, args.port)
	c.send_reset()

	# TODO set by args
	address = 0

	with open(args.output, 'wb') as file:
		try:
			while True:
				print_progress('Read address %s' % hex(address))

				c.read_step(args.address)
				value = c.get_reg(args.reg)
				# Probably wrong
				file.write(bin(value))
		except Exception as e:
			print(e)

		address += 16

	print('Firmware dumped..')


if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='This script can dump a firmware of ARM Cortex-M0 SoC also when readout protection is enabled.')
	parser.add_argument('-H', '--host', default='localhost', help='host to connect to')
	parser.add_argument('-p', '--port', type=int, default=4444, help='port to connect to')
	parser.add_argument('-n', '--no-input', action='store_true', help='prevent prompt')
	subparsers = parser.add_subparsers(help='select a sub-command')

	parser_find = subparsers.add_parser('search', help='search an address that access the memory')
	parser_find.add_argument('-a', '--address', type=lambda x: int(x, 0), default=0, help='start address')
	parser_find.set_defaults(func=search)

	parser_dump = subparsers.add_parser('dump', help='dump the firmware')
	parser_dump.add_argument('address', help='select the address')
	parser_dump.add_argument('reg', help='select the register')
	parser.add_argument('-o', '--output', default='image.bin', help='output file name')
	parser_dump.set_defaults(func=dump)

	args = parser.parse_args()
	try:
		args.func(args)
	finally:
		print('\n')


