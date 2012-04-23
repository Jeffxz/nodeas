import nodeas.*;
import nodeas.http.*;

trace("hello, world!");
var nodeas: Nodeas = new Nodeas();
trace(nodeas);
trace(Nodeas.getVersion());
Http.startlisten(8080, function() {
        trace("callback is called");
        });

