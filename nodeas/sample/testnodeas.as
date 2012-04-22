import nodeas.*;
trace("hello, world!");
var nodeas: Nodeas = new Nodeas();
trace(nodeas);
trace(Nodeas.getVersion());
Nodeas.startlisten(8080, function() {
        trace("callback is called");
        });
// trace(nodeas.getVersion());
// nodeas.listen("8080");
