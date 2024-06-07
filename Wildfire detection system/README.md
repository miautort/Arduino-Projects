This is a sort of a makeshift fire detection system, not that complicated, made with the premise that it detects wildfires in a forest. The assignment specified that I must use a NTC thermistor and a photoresistor for it so I stuck with that and didn't bother with humidity or gas detectors. 



I tested the sensors exclusively in the simulator because I did not have a reference sheet of the resistors I actually had on hand, and comparing temperatures with a DHT would have been a little bit inaccurate since they have different builds. The logic is that when temperature rises over a certain level and the light is dim there is a fire with a smoke cover. If there's no smoke cover then it's inaccurate to use the 35 degrees threshold since it could just be summer so the temperature thershold is increased. The LED turns on if there's a fire.



The block diagram was made in MS Paint this time (if it works it works), but this is the idealized version that has a lot of stuff and is way more accurate.

![block diagram](https://github.com/miautort/Arduino-Projects/assets/171256065/efbd9f2a-f0c9-4600-b87c-62bb440674ef)



This is how the circuit would look like, made in wokwi.

![image](https://github.com/miautort/Arduino-Projects/assets/171256065/db672c9e-23c6-4bbb-b6f8-8d16e6c7000b)



A simulation of it can be run here:
<https://wokwi.com/projects/399327533240168449>



