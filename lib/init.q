\d .ts

.utl.require "qutil/opts.q";

PKGNAME: .utl.PKGLOADING

.utl.addOpt["usetick";0b;`.ts.tickless];
.utl.parseArgs[];

.utl.require .utl.PKGLOADING,"/ldd.q"

stats:`eventcalls`lag!(0;0.n);
private.events:([id:enlist 0Ng] at:enlist 0Wp; interval:enlist 0.n; func:enlist (::) )

defaults.add: `interval`func # private.events 0Ng;

private.setnext:{[]
  now:.z.p;
  one_ns:`timespan$1;
  p: one_ns | min[private.events[;`at]]-now;
  if[not is_set[]; start ".ts.private.callback" ];
  private.set p;
  }

add:{[f;t;opts]
  d:defaults.add;
  if[ type[opts]=99h; d,:inter[key opts;key defaults.add]#opts ];
  tp: $[ type[t] in (-16h;-19h); `timestamp$.z.d+t; t];

  d[`id`func`at]:(id:rand 0Ng;f;tp);

  private.events,:d;
  private.setnext[];
  id
  }

getrow:{if[not x in key private.events;'notfound]; private.events[x] }

remove:{ delete from `.ts.private.events where id in x }

pending:{ exec id from private.events where at<=x }

private.callback:{[numevents]
  if[0=count ids:pending tstart:.z.p; :0];

  fire:{[f;at;id] stats[`lag]+:.z.p-at; @[eval;f,(at;id);{}]; };

  exec fire'[func;at;id] from private.events where id in ids;
  update at:at+interval from `.ts.private.events where id in ids, interval<>0.n;
  delete from `.ts.private.events where id in ids, interval=0.n;
  stats[`eventcalls]+:count ids;

  .z.s[numevents];
  private.setnext min private.events[;`at]
  }

\d .
