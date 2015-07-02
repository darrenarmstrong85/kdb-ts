{ if[-11h<>type key sopath:hsym`$.utl.PKGLOADING,"/ts.so";
     if[-11h<>type key cpath:hsym`$.utl.PKGLOADING,"/ts.c"; '"could not load or build ts.so"];
	 / build it and they will come#
     ];
  }[];

start:`ts 2:(`start;1)
stop:`ts 2:(`stop;1)

private.getnext:`ts 2:(`getnext;1);
private.setnext:`ts 2:(`setnext;1);
