#include "yocto_api.h"
#include "yocto_humidity.h"
#include "yocto_temperature.h"
#include "yocto_pressure.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

static void usage(void)
{
  cout << "usage: ymeteo                 (fetch any discovered device)" << endl;
  cout << "       ymeteo config          (config any discovered device)" << endl;
  exit(1);
}

int main(int argc, const char * argv[])
{
  string errmsg, target, ifconfig;
  YHumidity    *hsensor;
  YTemperature *tsensor;
  YPressure    *psensor;

  if (argc < 1) {
    usage();
  }

  // Setup the API to use local USB devices
  if (yRegisterHub("usb", errmsg) != YAPI_SUCCESS) {
    cerr << "RegisterHub error: " << errmsg << endl;
    return 1;
  }

  hsensor = yFirstHumidity();
  tsensor = yFirstTemperature();
  psensor = yFirstPressure();
  if (hsensor == NULL || tsensor == NULL || psensor == NULL) {
    cout << "No module connected (check USB cable)" << endl;
    return 1;
  }

  if (!hsensor->isOnline()) {
    cout << "Module not connected (check identification and USB cable)";
    return 1;
  }

  if (argc >= 2) {
      ifconfig = (string) argv[1];
  }

  if (ifconfig == "config") {
      cout << "multigraph ymeteo_temperature" << endl;
      cout << "graph_title YoctoMeteo Temperature" << endl;
      cout << "graph_args --base 1000 -l 0" << endl;
      cout << "graph_scale no" << endl;
      cout << "graph_category yocto" << endl;
      cout << "graph_info Temperature, as measured by YoctoMeteo." << endl;
      cout << "t.warning 25" << endl;
      cout << "t.critical 30" << endl;
      cout << "t.label T (°C)" << endl;
      cout << "t.info Temperature in °C" << endl;

      cout << "multigraph ymeteo_humidity" << endl;
      cout << "graph_title YoctoMeteo Humidity" << endl;
      cout << "graph_args --base 1000 -l 0" << endl;
      cout << "graph_scale no" << endl;
      cout << "graph_category yocto" << endl;
      cout << "graph_info Humidity, as measured by YoctoMeteo." << endl;
      cout << "h.warning 80" << endl;
      cout << "h.critical 100" << endl;
      cout << "h.label H (%RH)" << endl;
      cout << "h.info Humidity in %RH" << endl;

      cout << "multigraph ymeteo_pressure" << endl;
      cout << "graph_title YoctoMeteo Pressure" << endl;
      cout << "graph_args --base 1000 -l 0" << endl;
      cout << "graph_scale no" << endl;
      cout << "graph_category yocto" << endl;
      cout << "graph_info Pressure, as measured by YoctoMeteo." << endl;
      cout << "p.info P (hPa)" << endl;
      cout << "p.info Pressure in hPa" << endl;
  } else if (hsensor->isOnline()) {
    cout << "t.value " << tsensor->get_currentValue() << endl;
    cout << "h.value " << hsensor->get_currentValue() << endl;
    cout << "p.value " << psensor->get_currentValue() << endl;
  };
  yFreeAPI();

  return 0;
}
