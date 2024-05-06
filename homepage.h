String homePagePart1 = F(R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="refresh" content="10">
<title>Smart Steering Wheel</title>
<style>
  body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    text-align: center; /* Center-align all content */
  }

  header {
    background-color: #00a8e8;
    color: #fff;
    padding: 20px;
  }

  .content {
    padding: 20px;
  }

  .section {
    margin-bottom: 30px;
  }

  .section h2 {
    color: #333;
  }

  .section p {
    color: #666;
  }

  footer {
    background-color: #00a8e8;
    color: #fff;
    padding: 20px;
    width: 100%;
  }

  p {
    margin-top: 5px;
    margin-bottom: 5px;
  }

  ul {
    list-style-type: none;
    padding: 0;
    display: flex;
    justify-content: space-between; /* Evenly space the list items */
    flex-wrap: wrap; /* Allow items to wrap to the next line if needed */
  }

  li {
    flex: 1; /* Each item takes up equal space */
    margin-right: 10px; /* Adjust the spacing between photos */
    margin-left: 10px;
  }

  img {
    width: 100%; /* Make the images fill the container */
    height: 80%; /* Maintain aspect ratio */
    border-radius: 10px;
  }

  .container {
    position: relative;
    text-align: center;
    color: white;
  }

  .centered {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
  }

  .Bottom-centered {
    position: absolute;
    bottom: 5%;
    left: 50%;
    transform: translateX(-50%);
  }

  .cloudData {
    text-align: center; /* Center-align text */
  }

  .iframe-container {
    display: flex;
    justify-content: center;
    flex-wrap: wrap;
  }

  .iframe-container iframe {
    width: 450px;
    height: 260px;
    border: 1px solid #cccccc;
    margin: 10px;
  }
  .topnav {
  background-color: #00a8e8;
  overflow: hidden;
  display: flex;
  justify-content: center;
}

.topnav a {
  color: #f2f2f2;
  text-align: center;
  text-decoration: none;
  font-size: 17px;
  margin: 0 10px; /* Adjust the spacing between items */
}

.topnav a.active {
  background-color: #00a8e8;
  color: white;
}

</style>
</head>
<body>
  <header>
    <h1>Smart Steering Wheel</h1>
    <div class="topnav">
        <a class="active" href="#First">Home</a>
        <a href="#live-data">Live-data</a>
        <a href="#cloud-data">Cloud-data</a>
        <a href="#about-us">About-Us</a>
    </div>
  </header>

  <div class="First">
    <div id="First" class="section"></div>
        <h1><span style="color: #B28DFF">Welcome to The Smart Steering Wheel</span></h1>
        <h2><span style="color: #B28DFF">The future of driver safety</span></h2>
        <h2><span style="color: #B28DFF">Designed to keep you and your family safe</span></h2>
      </div>
  </div>

  <div class="second">
    <div id="live-data" class="section">
      <h2>Live Data</h2>
      <p>This section displays live data from the smart steering wheel.</p>
      <h2>Current Sensor Data</h2>
      <p>Temperature:)====="); String homePagePart2 = F(R"=====(°C</p>
      <p>Humidity:)====="); String homePagePart3 = F(R"=====( %</p>
      <p>BPM:)====="); String homePagePart4 = F(R"=====( m/s²</p>
      <p>Distance:)====="); String homePagePart5 = F(R"=====(</p>
      <p>SPO2:)====="); String homePagePart6 = F(R"=====( %</p>
      <p>Lati:)====="); String homePagePart7 = F(R"=====( °</p>
      <p>Long:)====="); String homePagePart8 = F(R"=====( °</p>
      <h3>Checks</h3>
      <p>Distance check:)====="); String homePagePart9 = F(R"=====( </p>
      <p>Temperature check:)====="); String homePagePart10 = F(R"=====( </p>
      <p>Heart rate check:)====="); String homePagePart11= F(R"=====( </p>
    </div>

    <div class="gps">
      <h1>Example google maps view</h1>
      <iframe src="https://www.google.com/maps/embed?pb=!1m17!1m12!1m3!1d1192.819153768307!2d-9.01098014328565!3d53.27809999303847!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m2!1m1!2zNTPCsDE2JzQxLjIiTiA5wrAwMCczNC45Ilc!5e0!3m2!1sen!2sie!4v1714605585421!5m2!1sen!2sie" width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
      <h2>Please paste this link into your search bar</h2>
      <p>https://www.google.com/maps?q= )====="); String homePagePart12 = F(R"=====(, )====="); String homePagePart13 = F(R"=====( </p>
    </div>
  </div>

  <div class="third"></div>
  <div id="cloud-data" class="section"></div>
  <div class="cloudData">
    <h1>Cloud data</h1>
    <h3>What you're seeing here is a cloud storage of all data received</h3>
    <h3>ThingSpeak is the cloud storage service we're using</h3>

    <div class="iframe-container">
      <div>
        <h3>Humidity</h3>
        <iframe src="https://thingspeak.com/channels/2413089/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=20&title=Humidity&type=line"></iframe>
      </div>
      <div>
        <h3>Temperature</h3>
        <iframe src="https://thingspeak.com/channels/2413089/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
      </div>
      <div>
        <h3>Heart Rate</h3>
        <iframe src="https://thingspeak.com/channels/2413089/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Bpm&type=line"></iframe>
      </div>
      <div>
        <h3>Blood Oxygen Level</h3>
        <iframe src="https://thingspeak.com/channels/2413089/charts/4?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
      </div>
    </div>
    
    <div class="centered-iframe">
      <div>
        <h3>Distance</h3>
        <iframe src="https://thingspeak.com/channels/2413089/charts/5?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
      </div>
    </div>
  </div>

  <div class="location">
    <h2>Last known location</h2>
    <iframe src="https://www.google.com/maps/embed?pb=!1m17!1m12!1m3!1d1192.819153768307!2d-9.01098014328565!3d53.27809999303847!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m2!1m1!2zNTPCsDE2JzQxLjIiTiA5wrAwMCczNC45Ilc!5e0!3m2!1sen!2sie!4v1714605585421!5m2!1sen!2sie" width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
    <h2>Please paste this link into your search bar</h2>
    <p>https://www.google.com/maps?q= 53.2781416912305, -9.009722187380415</p>
  </div>

  <div class="aboutUs">
    <div id="about-us" class="section"></div>
    <h1>About Us</h1>
    <p>Hello! this is a quick demonstaration video of one of the features of this project</p>
    <iframe src="https://drive.google.com/file/d/15kRM8zC1zM4FC2tHMV-vDtW1JI8wqPy7/view?usp=drive_link" width="575" height="320" allow="autoplay"></iframe>
  </div>

  <h1>Why?</h1>
  <p>In 2022, the World Health Organization reported 1,350,000 road traffic-related deaths worldwide,</p>
  <p>with an additional 50,000,000 people injured due to accidents. In Ireland, the Road Safety Authority (RSA)</p>
  <p>revealed a record-high of 155 fatalities in road accidents during the same year,</p>
  <p>with over 1000 additional injuries. To address this, I am developing an in-vehicle</p>
  <p>device equipped with safety and attention-keeping features, Aimed at our elderly drivers & pedestrians</p>
  <p>to help keep them protected on our roads.</p>

  <h2>Personal reason?</h2>
  <p>I drive myself and spend a majority of my days driving, I've had some close calls some my fault some</p>
  <p>other peoples faults, but a lot of these happen in the country side where people may not spot the accident</p>
  <p>happening, that scares me, how long would it take for emergency services to find me and would it be too late</p>
  <p>I know i'm not alone in this matter so I thought, why not take matters into my own hand and</p>
  <p>design a device "The Smart Steering Wheel" to help calm my nerves and help ensure my safety and others</p>
  <p>like me, and also keeping our conscience clear that we haven't ingured anyone else with our</p>
  <p>automatic breaking system.</p>

  <h1>Components & Uses</h1>
  <h2>First component used in this project is a DHT11</h2>
  <p>We use the DHT11 to monitor the humidity and temperature</p>
  <p>inside the cabin, When the temperature is hot and the heart rate is dropping</p>
  <p>its registered as the driver is falling asleep and action needs to be taken</p>
  <p>a signal will be sent to the temperature console in the car to put more cold air</p>
  <p>Into the cabin waking the driver up and allowing them to keep their alertness</p>
  <p>once the heartrate is registered as average again, the temperature console readjusts</p>
  <p>the same thing happens when the humidity gets too high as this affects the</p>
  <p>the drivers tiredness, so adjusting for more air to flow in combating the issues</p>
  <h1> </h1>
  <h2>Second component used in this project is a MAX30100</h2>
  <p>The MAX30100 is a Pulse Oximeter & Heart rate sensor</p>
  <p>The use of this sensor is to monitor the heartrate of the driver and store</p>
  <p>data it collects to Thingspeak for driver to see his heart data.</p>
  <p>This sensor also detects if the heart rate is dangerously low or dangerously high</p>
  <p>dectecting if the driver is having a heart attack or a heart related issue</p>
  <p>it will then activate the hazard lights and apply the break lightly</p>
  <p>bringing the vehicle to a stop and then contacting a emergency contact and </p>
  <p>emergency services, sending them the current GPS location of the vehicle</p>
  <p>allowing for the driver to be found fast increasing the chance of survival</p>
  <h2>Third component used in this project is a HC-SR04</h2>
  <p>The HS-SR04 is a Ultrasonic Sensor</p>
  <p>The use of this sensor is to track see if there's any pedestrians or obstacles</p>
  <p>infront of the car, if the Ultrasonic detects a obstacle or pedestrian infront</p>
  <p>of the car, it will apply the breaks and attempt to slow down in time before</p>
  <p>collision with the object is made, if collision is innevitable it will report</p>
  <p>the gps signal to the emergency services and emergency contact giving the pedestrian &</p>
  <p>driver the best chance of survival</p>
  <h2>Fourth component used in this project is a A9G</h2>
  <p>The A9G is a GPS & GMS module</p>
  <p>The use of this sensor is to track the drivers position at all times</p>
  <p>this could be used for security but more imporantly safety and</p>
  <p>fast response from emergency services with the most up to date information</p>
  <p>about the patient they will be receving allowing them to be more prepared</p>
  <p>the module will send the driver's current Blood oxygen level and heartrate data</p>
  <p>along with the current GPS location to emergency services and a emergency contact</p>
  <p>It will also gather if it's a collision sending the emergency services information that their is</p>
  <p>multiple casulaties at the scene alllowing them to bring more ambulances if needed</p>
  <h2>The final component used in this project is a ESP32</h2>
  <p>The ESP32 is a controller for all the modules and devices connected to it</p>
  <p>The ESP32 also contains a bluetooth and more importanly wifi modules to host web servers</p>
  <p>Without the ESP32, this project would refuse to function, you also wouldn't</p>
  <p>be reading this current text without it, with low power consumption and good versatility</p>
  <p>with a broad amount of ports to house every component needed, it offers us the best</p>
  <p>devlopment ease of use we can get.</p>

  <footer>
    <p>&copy; 2024 Smart Steering Wheel</p>
  </footer>
</body>
</html>
      )=====");