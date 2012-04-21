import nodeas.*;
trace("hello, world!");
var nodeas: Nodeas = new Nodeas();
trace(nodeas);
trace(Nodeas.getVersion());
trace(getSize(nodeas));
trace(Nodeas.startlisten(8080));
// trace(nodeas.getVersion());
// nodeas.listen("8080");
