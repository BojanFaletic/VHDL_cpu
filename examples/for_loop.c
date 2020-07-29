

int main(){
  int *b = new int;

  for (int i=0; i<10; i++){
    *b = i;
  }
}


/*
  .HW
  // register are here

  .RAM
  0x00 // physical memory

  .ROM
  0x00 // a
  0x01 // +1
  0x0a // 10

  .DATA
  LOAD 0x00
  ADD 0x01
  STORE 0x00 // store to physical memory
  CMP_LT 0x02
  JMP_EQ 0x02 // jump to ADD instruction


 */
