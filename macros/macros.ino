const uint8_t PROGMEM a_btn{2};
const uint8_t PROGMEM c_btn{4};
const uint8_t PROGMEM d_btn{5};
const uint8_t PROGMEM b_btn{3};
const uint8_t PROGMEM e_btn{6};
const uint8_t PROGMEM f_btn{7};
const uint8_t PROGMEM k_btn{8};

boolean prev_a_btn = false;
boolean prev_c_btn = false;
boolean prev_d_btn = false;
boolean prev_b_btn = false;
boolean prev_e_btn = false;
boolean prev_f_btn = false;
boolean prev_k_btn = false;

void btn_cb(bool new_val, bool &old_val, char index) {
  if (new_val == old_val)
    return;
  old_val = new_val;
  Serial.print(index);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting..");

  pinMode(a_btn, INPUT);
  pinMode(c_btn, INPUT);
  pinMode(d_btn, INPUT);
  pinMode(b_btn, INPUT);
  pinMode(e_btn, INPUT);
  pinMode(f_btn, INPUT);
  pinMode(k_btn, INPUT);
}

void loop() {
  btn_cb(digitalRead(a_btn) == LOW, prev_a_btn, 'a'); 
  btn_cb(digitalRead(b_btn) == LOW, prev_b_btn, 'b');
  btn_cb(digitalRead(c_btn) == LOW, prev_c_btn, 'c');
  btn_cb(digitalRead(d_btn) == LOW, prev_d_btn, 'd');
  btn_cb(digitalRead(e_btn) == LOW, prev_e_btn, 'e');
  btn_cb(digitalRead(f_btn) == LOW, prev_f_btn, 'f');
}
