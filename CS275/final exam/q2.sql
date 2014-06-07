#create tables, straight from teh question

DROP TABLE IF EXISTS manager2employee;
DROP TABLE IF EXISTS employee;
DROP TABLE IF EXISTS managers;

CREATE TABLE managers(
	id INT PRIMARY KEY AUTO_INCREMENT,
	ssn INT NOT NULL,
	name VARCHAR(255),
	department VARCHAR(255)
)engine=innodb;

CREATE TABLE employee(
	id INT PRIMARY KEY AUTO_INCREMENT,
	ssn INT NOT NULL,
	name VARCHAR(255),
	boss INT,
	FOREIGN KEY (boss) REFERENCES managers(id)
)engine=innodb;

#insert dummy values
INSERT INTO managers () VALUES (1, 1, "man1", "1");
INSERT INTO managers () VALUES (2, 2, "man2", "2");
INSERT INTO managers () VALUES (3, 3, "man3", "3");
INSERT INTO employee () VALUES (1, 1, "emp1", 1);
INSERT INTO employee () VALUES (2, 2, "emp2", 2);
INSERT INTO employee () VALUES (3, 3, "emp3", 3);


#create the new relationship table
#by copying the manger table
create table manager2employee (
mID INT,
eID INT,
foreign key (mID) references managers (id),
foreign key (eID) references employee (id)
) engine = innodb;

#copy the managers into the new relationship table
INSERT manager2employee SELECT id, NULL FROM managers;

#update the table with the employee/boss info, as it exists presently
UPDATE manager2employee AS m2e
  INNER JOIN employee AS ee ON m2e.mID = ee.boss
SET m2e.eID = ee.id;

#find the foreign key constraint and store it in @const_name
SET @const_name = ( SELECT CONSTRAINT_NAME
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME =  'employee'
AND CONSTRAINT_NAME <>  'PRIMARY' );

#make an alter table statement from the foreign key constraint
SET @s := CONCAT(  "ALTER TABLE employee DROP FOREIGN KEY ", @const_name ) ;
PREPARE stmt FROM @s ;

#execute the carefully devised statement
EXECUTE stmt;

#get rid of the boss column
ALTER TABLE employee DROP COLUMN boss;

#add some more dummy relationships
INSERT INTO manager2employee () VALUES (1,3);
INSERT INTO manager2employee () VALUES (3,1);
INSERT INTO manager2employee () VALUES (1,2);
INSERT INTO manager2employee () VALUES (2,3);

# Query to get a list of employees and managers
# The updated version should show all employee manager pairs
SELECT employee.name, managers.name AS `boss` FROM employee 
INNER JOIN manager2employee ON manager2employee.eID = employee.id
INNER JOIN managers ON manager2employee.mID = managers.id;