#Script 1
#Your name: Eric Rouse
#Your engr user name: rousee

DROP TABLE IF EXISTS airport;
DROP TABLE IF EXISTS apType;
	
#Your code goes below here

#Create the table 'apType' with an auto incrementing integer 'id' 
#field and a 255 variable length string 'type' which cannot be null
#10pts

create table apType(
id int primary key auto_increment,
type varchar(255) NOT NULL
) engine = innoDB;


#Create the table 'airport' with an autio incrementing 'id' field as
#the primary key, a 255 character variable length string field for 'name'
#which cannot be null, an integer 'rwyCount', 'lat' and 'lon' as floats
#and an integer 'type' that corrisponds to a type id which must be from the apType table
#10pts

create table airport(
id int primary key auto_increment,
name varchar(255) NOT NULL,
rwyCount int,
lat float,
lon float,
type int NOT NULL,
foreign key(type) references apType(id)
) engine = innoDB;

#Insert the types 'private', 'public' and 'military' into 'apType'
#5pts
insert into apType () values (NULL, 'private');
insert into apType () values (NULL, 'public');
insert into apType () values (NULL, 'military');

#Insert the airport 'Kahului' with 1 runway, a type of 'public' and a lat/lon of 20.898611/-156.430556
#5pts
insert into airport () values (NULL, 'Kahului', 1, 20.898611, -156.430556, (select id from apType where type = 'public'));

#Insert the airport 'Portland' with 3 runways a type of 'public' and a lat/lon of 45.588611/-122.5975
#5pts
insert into airport () values (NULL, 'Portland', 3, 45.588611, -122.5975, (select id from apType where type = 'public'));

#Update the runway count to 2 for Kahului airport
#5pts
update airport set rwyCount=2 where name = 'Kahului';

#Delete Portland airport
#5pts
delete from airport where name = 'Portland';

#Attempt to add an airport with an invalid type id and have it fail
#5pts
#two ways to fail, invalid query returns null:
insert into airport () values (NULL, 'Fake E. Fakerson', 1000000, 12.2, 22.1, (select id from apType where type = 'invalid'));
#and just puting a bad id in the id column:
insert into airport () values (NULL, 'Fake E. Fakerson', 1000000, 12.2, 22.1, 33);
