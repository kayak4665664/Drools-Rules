# Randomly-generating-of-Drools-rules
These programs randomly generate Drools rules &amp; check the Drools rules output by the machine learning model. They are used to make machine learning training sets. These are part of a conflict detection method for the control logic rules of the Internet of Things system.  
这些程序随机生成Drools规则 & 检测机器学习模型生成的Drools规则。它们用于制作机器学习训练集。 这些是物联网系统控制逻辑规则冲突检测方法的一部分。

Time: 2020 Summer

The output of `generate_rules_of_room1.cpp`, `generate_rules_of_room2.cpp` and `generate_rules_of_room3.cpp` likes:
``` drools
rule "rule2"
	dialect "mvel"
	when
		$environ : Environ( innerHumidity != 5 , innerLightRay <= 20 , outerTemperature >= 21 , outerHumidity >= 8 , outerLightRay <= 23 , peopleNum == 8 )
		Demonstrator( state == false )
		$light : Light( state == 0 )
		XiaoMing( state == true )
		$airHumidifier : AirHumidifier( )
		$projector : Projector( )
	then
		$environ.setOuterTemperature( 30 );
		$environ.setOuterLightRay( 6 );
		$light.setState( 1 );
		$airHumidifier.setIsOn( 1 );
		$airHumidifier.set_Humidity( 19 );
		$projector.setIsOn( false );
		update( $environ );
		update( $light );
		update( $airHumidifier );
		update( $projector );
end
//note:when the indoor humidity is not equal to 5 % and the indoor light intensity is less than or equal to 20 lx and the outdoor temperature is greater than or equal to 21 °C and the outdoor humidity is greater than or equal to 8 % and the outdoor light intensity is less than or equal to 23 lx and the number of people is equal to 8 and the demonstrator isn't in the room and the light is turned off and XiaoMing is in the room, then the student sets the outdoor temperature to 30 °C and sets the outdoor light intensity to 6 lx and turns on the light and turns on the air humidifier and sets the humidity of the air humidifier to 19 gal/day and turns off the projector.
```

The output of `generate_rules_of_ship2.cpp` likes:
``` drools
rule "rule1"
	dialect "mvel"
	when
		$aDA : ADA( bulletNum < 97723 , highSpeed >= 2780 , isAimed != false , isDestroyed != true , lowSpeed < 234 , mediumSpeed >= 1999 , shutSpeed > 2012 , state != 0 )
		$airCraft : AirCraft( flyDirection != 103 )
		$warShip : WarShip( destroyedLevel > 3 , shipSpeed > 2 )
	then
		$aDA.setBulletNum( 33406 );
		$aDA.setIsDestroyed( true );
		$aDA.setMediumSpeed( 454 );
		$aDA.setShutSpeed( 7987 );
		$aDA.setState( 1 );
		$airCraft.setFlySpeed( 21 );
		$airCraft.setIsShut( true );
		$airCraft.setShutSpeed( 1219 );
		$warShip.setDestroyedLevel( 9 );
		$warShip.setIsWoFang( true );
end
//note:when the number of bullets of the ADA is less than 97723 and the high rate of fire of the ADA is greater than or equal to 2780 RPM and the ADA aimed at the target and the ADA isn't destroyed and the low rate of fire of the ADA is less than 234 RPM and the medium rate of fire of the ADA is greater than or equal to 1999 RPM and the rate of fire of the ADA is greater than 2012 RPM and the ADA is on and the direction of the aircraft is not equal to 103 ° and the extent of damage to the warship is greater than 3 and the speed of the warship is greater than 2 kn, then the control system sets the number of bullets of the ADA to 33406 and destroyed the ADA and sets the medium rate of fire of the ADA to 454 RPM and sets the rate of fire of the ADA to 7987 RPM and turns on the ADA and sets the speed of the aircraft to 21 km/h and makes the aircraft shoot and sets the rate of fire of the aircraft to 1219 RPM and sets the extent of damage to the warship to 9 and makes the warship belong to us.
```

The output of `check_the_rules.cpp` likes:
``` drools
//Number: 8
//Score: 0.077
//The standard rule:
rule "rule2"
	dialect "mvel"
	when
		$environ : Environ( innerTemperature == 29 , innerHumidity < 8 , innerLightRay != 8 , outerHumidity == 9 )
		Demonstrator( state == true )
		Speaker( state == true )
		XiaoMing( state == true )
		$light : Light( )
	then
		$environ.setOuterHumidity( 26 );
		$environ.setOuterLightRay( 15 );
		$environ.setPeopleNum( 2 );
		$light.setState( 1 );
		update( $environ );
		update( $light );
end

//The different rule:
rule "rule2"
	dialect "mvel"
	when
		$microPhone : MicroPhone( volumn != 26 )
	then
		$microPhone.setIsOn( 0 );
		update( $microPhone );
end

//The differences:
//The logical relationship of the conditions is different.
//Class: MicroPhone.
//Class: MicroPhone, setIsOn.
//update( $microPhone ).
//Some classes or members are missing.
```
```
//The total number of comparisons: 9
//The total number of differences: 9
//Values compairsion disabled
//The difference rate: 100.000%
//The average score: 0.211
//Warning: The number of rules of the compared drl may be more than the number of standard drl.
```