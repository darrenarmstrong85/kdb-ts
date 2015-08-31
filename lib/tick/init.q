cb:""
is_set:{0<>count cb}
nextevent:0Wp;

private.set:{system "t ", string `int$`time$`timespan$1e6*ceiling x%1e6}
start:{[f] cb::f;}
stop:{ cb::"";}

.z.ts:{get[cb][]; private.setnext[]}
