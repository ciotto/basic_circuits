const int ROWS[8] = {A0, A1, A2, A3, A4, A5, 10, 11};
const int COLUMNS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int LOVE[8][8] = {
  {0, 1, 1, 0, 0, 0, 1, 0},
  {1, 0, 0, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0} 
};

int ALL[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

int m[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

void reset_leds() {
   for (int x=0; x < 8; x++) {
    for (int y=0; y < 8; y++) {
      m[y][x] = 0;
    }
  }
}


void set_led(int x, int y, int light) {
  m[y][x] = light;
}

void set_row(int y, int row[8], boolean reset) {
  if (reset) {
    //reset_led();
  }
  
  for (int x=0; x < 8; x++) {
    //set_led(x, y, row[x], false);
  }
}

void setup() {
  Serial.begin (9600);
  while (!Serial);
  
  for (int i=0; i < 8; i++) {
    pinMode(ROWS[i], OUTPUT);
    pinMode(COLUMNS[i], OUTPUT);
    
    digitalWrite(ROWS[i], 0);
    digitalWrite(COLUMNS[i], 1);
  }
}

void update_led(int d) {
  for (int i=0; i < d / 8; i++) {
    for (int y=0; y < 8; y++) {
      if (y>0) {
        digitalWrite(ROWS[y-1], 0);
      } else {
        digitalWrite(ROWS[7], 0);
      }
      for (int x=0; x < 8; x++) {
        //Serial.print(columns[x]);
  
        digitalWrite(COLUMNS[x], !m[y][x]);
      }
      //Serial.println();
      digitalWrite(ROWS[y], 1);
      delay(1);
    }

    delay(1);
  }
}
void update_led() {
  update_led(1);
}

void matrix_loop(int matrix[8][8]) {
  for (int x=0; x < 8; x++) {
    for (int y=0; y < 8; y++) {
      set_led(x, y, matrix[y][x]);
    }
    update_led(15);
  }
}

void step_loop() {
  for (int x=0; x < 8; x++) {
    for (int y=0; y < 8; y++) {
      reset_leds();
      set_led(x, y, true);
      update_led(100);
    }
  }
}

void step_loop_columns() {
  for (int x=0; x < 8; x++) {
    reset_leds();
    for (int y=0; y < 8; y++) {
      set_led(x, y, true);
    }
    update_led(100);
  }
}

void step_loop_row(int y) {
  for (int x=0; x < 8; x++) {
    set_led(x, y, true);
  }
  update_led(1000);
}

void step_loop_rows() {
  for (int y=0; y < 8; y++) {
    reset_leds();
    for (int x=0; x < 8; x++) {
      set_led(x, y, true);
    }
    update_led(1000);
  }
}

void step_led(int x, int y) {
  reset_leds();
  set_led(x, y, true);
  update_led(1000);
}

void loop() {
  //matrix_loop(LOVE);
  //matrix_loop(ALL);
  //step_loop();
  //step_loop_columns();
  //step_loop_rows();
  step_loop_row(5);

  //step_led(3, 1);
  //step_led(5, 3);
  //step_led(6, 5);
  //step_led(0, 0);
}
