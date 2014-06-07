#Create tables queries:

#buses table
CREATE TABLE buses(
busNo INT PRIMARY KEY AUTO_INCREMENT
) ENGINE = INNODB;

#positions table
CREATE TABLE positions(
pID INT PRIMARY KEY AUTO_INCREMENT ,
busNo INT NOT NULL ,
lat FLOAT NOT NULL ,
lng FLOAT NOT NULL ,
tmstp TIMESTAMP,
accuracy INT,
FOREIGN KEY ( busNo ) REFERENCES buses (busNo)
) ENGINE = INNODB;

#stops table
CREATE TABLE stops(
sID INT PRIMARY KEY AUTO_INCREMENT ,
name VARCHAR( 255 ) ,
lat FLOAT NOT NULL ,
lng FLOAT NOT NULL
) ENGINE = INNODB

#drivers table
CREATE TABLE drivers(
dID INT PRIMARY KEY AUTO_INCREMENT ,
fname VARCHAR( 255 ) ,
lname VARCHAR( 255 ) ,
rating INT
) ENGINE = INNODB;

#bus and driver relationship table
CREATE TABLE busanddriver(
bus INT NOT NULL ,
driver INT NOT NULL ,
FOREIGN KEY ( bus ) REFERENCES buses( busNo ) ,
FOREIGN KEY ( driver ) REFERENCES drivers( dID )
) ENGINE = INNODB;

#route tables
CREATE TABLE routes(
route INT PRIMARY KEY ,
bus INT,
FOREIGN KEY ( bus ) REFERENCES buses( busNo )
) ENGINE = INNODB;
#populate routes table
INSERT INTO routes( ) 
VALUES ( 1, NULL ); 
INSERT INTO routes( ) 
VALUES ( 2, NULL );
INSERT INTO routes( ) 
VALUES ( 3, NULL ); 
INSERT INTO routes( ) 
VALUES ( 4, NULL );
#other route tables
CREATE TABLE route1(
stop INT,
FOREIGN KEY (stop) REFERENCES stops ( sID)
) ENGINE = INNODB;
CREATE TABLE route2(
stop INT,
FOREIGN KEY (stop) REFERENCES stops ( sID)
) ENGINE = INNODB;
CREATE TABLE route3(
stop INT,
FOREIGN KEY (stop) REFERENCES stops ( sID)
) ENGINE = INNODB;
CREATE TABLE route4(
stop INT,
FOREIGN KEY (stop) REFERENCES stops ( sID)
) ENGINE = INNODB;