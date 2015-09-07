cb:""
is_set:{0<>count cb}
nextevent:0Wp;

private.set:{system "t ", string 1|`int$`time$x}
start:{[f] cb::f;}
stop:{ system "t 0"; cb::"";}

.z.ts:{get[cb][]; private.setnext[]}
