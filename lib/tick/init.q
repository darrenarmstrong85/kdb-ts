cb:""
is_set:{all 0<>(count cb;system"t")}
nextevent:0Wp;

private.set:{nextevent::.z.p+x}

start:{[f] cb::f; system"t 1"}
stop:{ cb::""; system"t 0"}

.z.ts:{if[nextevent<=x;get[cb][]]}
