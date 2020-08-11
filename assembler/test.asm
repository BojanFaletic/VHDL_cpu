; comments
main: LOAD #0x00
add1: ADD #5
      CMP_LT #10
      JMP_EQ add1
      JMP aa
aa: JMP main
