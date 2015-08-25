localpath:first ` vs .utl.FILELOADING;

{ if[-11h<>type key sopath:hsym`$string[localpath],"/ts.so";
     if[any -11h<>type each key each cpath:hsym`$string[localpath],/: ("/ts.c";"/Makefile"); '"could not load or build ts.so"];
     show system "make"
     ];
  }[];

libpath:` sv (localpath;`ts);

start:libpath 2:(`start;1);
stop:libpath 2:(`stop;1);
is_set:libpath 2:(`is_timer_set;1);

private.getnext:libpath 2:(`getnext;1);
private.set:libpath 2:(`setnext;1);

private.setnext:{[p]
  private.set t:(0.0n+1)|p-now:.z.p;
  }

private.callback:{[dummy] 0N!(`callback;.z.p;dummy) };
