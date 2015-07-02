{ if[-11h<>type key sopath:hsym`$.utl.PKGLOADING,"/ts.so";
     if[-11h<>type key cpath:hsym`$.utl.PKGLOADING,"/ts.c"; '"could not load or build ts.so"];
	 / build it and they will come#
     ];
  }[];

libpath:"/" sv (system"cd";"ts");

start:libpath 2:(`start;1)
stop:libpath 2:(`stop;1)

private.getnext:libpath 2:(`getnext;1);
private.setnext:libpath 2:(`setnext;1);
