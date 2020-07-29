int inc_a(int a){
  return a++;
}

void main(){
  const int a = 8;
  const int b = inc_a(a);
}

/*

  .RAM
  0x00 //a
  0x00 //b

  .ROM
  0x8
  0x1

  .DATA
  LOAD 0x0;
  STORE 0x00; // store a
  PUSH R0;
  PUSH SP;

  POP R0;
  INC 0x1;
  POP R1;
  PUSH R0;
  JMP R1;
  POP R0;
  STORE 0x01; // store b
 */
