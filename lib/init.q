\d .ts

.utl.require .utl.PKGLOADING,"/ldd.q"

PKGNAME: .utl.PKGLOADING

private.events:([id:enlist 0Ng] at:enlist 0Wp; interval:enlist 0.n; func:enlist (::) )

defaults.add: `interval`func # private.events 0Ng;

add:{[f;t;opts]
  d:defaults.add;
  if[ type[opts]=99h; d,:inter[key opts;key defaults.add]#opts ];
  tp: $[ type[t] in (-16h-19h); `timestamp$.z.d+t; t];

  d[`id`func`at]:(id:rand 0Ng;f;tp);
  private.events,:d;

  if[not is_set[]; start ".ts.private.callback" ];
  private.setnext min private.events[;`at];
  id
  }

pending:{select from private.events where at<=x}

private.callback:{[numevents]
  if[0=count pending tstart:.z.p; :0];

  fire:{[f;at;id] .[f;(at;id);{}]; };

  exec fire'[func;at;id] from private.events where at<=tstart;
  update at:at+interval from `.ts.private.events where interval<>0.n;
  delete from `.ts.private.events where at<=tstart, interval=0.n;

  .z.s[numevents];
  private.setnext min private.events[;`at]
  }

\d .
