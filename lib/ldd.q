localpath:first ` vs .utl.FILELOADING;

if[-11h<>type key sopath:` sv (localpath;`os;.z.o;`ts.so);
   tickless:0b
   ];

$[ not tickless;
   system "l ", 1 _ string ` sv (localpath;`tick;`init.q);
   [  libpath:` sv (first ` vs sopath;`ts);

      start_int:libpath 2:(`start;1);
      stop:libpath 2:(`stop;1);
      is_set:libpath 2:(`is_timer_set;1);

      private.getnext:libpath 2:(`getnext;1);
      private.set:libpath 2:(`setnext;1);
      start:{start_int ".ts.private.callback"; private.setnext min private.events[;`at] }
      ]
   ];
   
private.callback:{[dummy] 0N!(`callback;.z.p;dummy) };
