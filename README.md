# 2024_CAPSTONE_ConnectTheFlow
Final Project for Cohort 14 
Start 12.2.24 -- Present on 12.13.24

the purpose of this project is to prototype an art piece for the city of Albuquerque that uses IOT devices. 


2024 CAPSTONE IOT
PROJECT OVERVIEW
Operation Bio Drop is a combination water fountain and vending machine that is part of a larger series of art pieces that will be places in local business, museums and or community centers, and possibly in the future, in outdoor spaces.
The theme is an extension of an art exhibition series began in 2023 called Connect the Flow. which reflected on the mind-body connection and its relationship to overall wellness.
This current iteration of the series will seek to ENGAGE, EDUCATE and ENDEAR viewers. Educational topics will range from environmental issues such as erosion and pollinator habitats, health and wellness awareness such body systems, and cultural issues.
MOTIVATION PROBLEMS TO SOLVE
In this social media society, it is common to feel disconnected form others as well as from one’s own body. This project seeks to provide an engaging way to educate the public about issues and endear them to one another and the city of Albuquerque through common goals and community building.
COMPONENTS
Particle Photon 2
OLED screen
Ultrasonic distance sensor
Relay
Water Pump
Neo pixel strip
Piezo pressure sensor
Stepper motor
3D printed parts, including an Archimedean screw
Laser cut components
A Lot of wood glue
FUNCTIONALITY and CODE
Thes device has two major functions.
The first, is that of a drinking fountain. Due to its size, I have decided to designate it as a drinking fountain for bees. The small amount of water gathered will be poured into a small shallow dish on the top of the device. In the future, there will be a load cell to check the weight of this container to prompt refilling, and or send data to the dashboard about how much water is being used.
STEP 1: The OLED screen prompts passersby to get water, (“Do you want to bathe a bee?”. In the future, the motion sensor will trigger the lights when anyone is a range of 3 feet. Its normal state will be asleep to save energy.
STEP 2: The ultrasonic sensor is triggered within a distance of 1 cm. A relay attached to a water pump is triggered and water is dispensed. When the cup is moved out of range, the water stops.
At the same time the relay is triggered, data is sent to a feed that tracks the number of interactions. In the future, I will be adding a location tracker as well.
STEP 3: After the really stop, the OLED thanks the visitor and prompts them to touch the face of the panel, under which a piezo pressure sensor is placed. The sensor is programed using the “high sticker” concert. Upon touch, the lights fill according to strength of pressure.
There are 60 pixels on the strip. The OLED will message the user at each try. If the pixels reach the end point and pixel number 59, they receive a “well done” message and a prompt to wait for a prize. If they do not reach this pixel, the OLED will prompt them to try again.
If the end pixel is reached, the stepper motor will be triggered to turn and release a seed infused paper via a wire-type vending method. An Archimedean screw was 3D printed for this task, but issues with scale arose and it was replaced with a wire.
ISSUES and CHALLANGES:
One of the first intended components, a load cell, which was meant to collect data on weight was attempted but abandoned due to wildly inaccurate readings. This took up valuable time before then.
Scale was an issue for this project. Larger size earns more material cost and difficulty in storage. I was committed to a smaller size from the outset, and seven attempts and 3d printing and decking laser cutting files confirmed this choice. However, this caused a series of other problems.
Ideally, It would have been better to have one function in a box with an area of about 8x10. Trying to fit all the components inside was difficult and time consuming. In the end, there were concessions made and some components, such as the Archimedean screw, were abandoned.
The vending machine portion does not currently work, needing a housing unit to help push the items through the coil or spiral.
Overall challenges included combining code into a master draft and (keeping it from breaking) and managing the other required tasks.2024 CAPSTONE IOT
PROJECT OVERVIEW
Connect the Flow - Operation Bio Drop is a combination drinking fountain or water bottle refill station and a vending machine that drops seeds or educational materials.
It is part of a larger series of art pieces that began in 2023.
MOTIVATION
The parent series, Connect the Flow (November 2023) focused on the mind-body connection. For this project, I wanted to create a representation of the digestive system, specifically surrounding the role of the gallbladder and the importance of a diverse gut microbiome.
This tear drop shape, which also looks like an onion or a seed, or various other possibilities, is a prominent feature of my artwork. It is the shape of life. I began to make this connection in 2019 after landing in the emergency room with a kidney stone.
Because of that, I wanted to create an art piece that functionally and educationally promotes hydration and biodiversity. This was made even more meaningful to me after ending up in the emergency room during the second week of November.
This coincided with our second midterm. I ended up losing my gallbladder and missing out on one of the projects I was most interested in – the self-watering plant system.
Therefore, I took this opportunity to use components of that project in my Capstone. It also allowed me to look at solving problems surround issues I am interested in.
I was inspired by the outdoor nature of the project. In the Rail Trail proposal slides, I specifically noted the slide about traditional, medicinal plants.
Unfortunately, the gallbladder gazebo will have to wait.
What i decided to focus on for this project was biodiversity of plants as a way to promote habitat for pollinators such as bees.
As a companion to a human sized drinking fountain, this little Bee Boo Box would encourage passersby to collect water and “bathe the bees.”
Problems I am hoping to explore:
Community building
Awareness of internal and external wellness
Let's look at how it works:
COMPONENTS
Particle Photon 2
OLED screen
Ultrasonic distance sensor
Relay
Water Pump
Neo pixel strip
Piezo pressure sensor
Stepper motor
3D printed parts, including an Archimedean screw
Laser cut components
Wood saw (thank you Z)
A Lot of wood glue
FUNCTIONALITY and CODE
This device has two major functions.
The first, is that of a drinking fountain. In this case, it is a drinking fountain for bees. The small amount of water gathered will be poured into a small shallow dish on the top of the device and the seeds may be planted in provided smart planters or taken home to be planted there.
STEP 1: The OLED screen prompts passersby to get water, (“Do you want to bathe a bee?”. In the future, the motion sensor will trigger the lights when anyone is a range of 3 feet. Its normal state will be asleep to save energy.
STEP 2: When the cup is inserted, the ultrasonic sensor is triggered. A relay attached to a water pump is triggered and water is dispensed. When the cup is moved out of range, the water stops.
At the same time the relay is triggered, data is sent to a feed that tracks the number of interactions. In the future, I will be adding a location tracker as well.
STEP 3: After the  relay stops, the OLED thanks the visitor and prompts them to touch the face of the panel, under which a piezo pressure sensor is placed. The sensor is programmed using the “high striker carnival game” concept. The strength of pressure determines how far the pixels move.
There are 60 pixels on the strip. The OLED will message the user at each try. The goal is to reach the end pixel, which is indicated in white.  If any other pixel is reached, the screen will ask them to try again.
Once the end pixel is reached, a “well done” message appears and a prompt to wait for their seeds is given. The stepper motor is triggered at this point, turning a wire-coil that moves and finally drops a recycled paper infused with seeds below.
Issues and challenges:
To begin with, I was not able to get the vending machine to work. One reason was space – there were too many components int he 8x10 area to really get them all to work.
Scale of 3D prints and laser cuts was another issue– sometimes measuring twice is not enough!
Hardware issues such as wiring that gets knocked loose of crossed and software eros causing the microcontroller to stop receiving code.
FUTURE PLANS
I plan to make a series of boxes that have isolated functions. The first is the fountain and the next is the seed vending machine.  My original plan before enrolling in this boot camp was to create a scavenger hunt around the city.
Partnering with local businesses along the rail trail and beyond, these interactive boxes will tell stories and educate the community of Albuquerque.
I would eventually like to create biannual or quarterly scavenger hunts that use IoT to gather data in how the boxes are being experienced. I have a lot to learn, but the seed has already been planted. Operation bio drop is on its way!
