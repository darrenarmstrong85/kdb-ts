cb:""
is_set:{all 0<>(count cb;system"t")}
nextevent:0Wp;

private.set:{nextevent::.z.p+x}

start:{[f] cb::f;}

.z.ts:{if[nextevent<=x;get[cb][]]}

\t 1
