#Script 2
#Your name: Eric Rouse
#Your engr user name: rousee

#Select the customername of customers from the country 'USA'
#10 pts
select customerName from customers where country = 'USA';

#Select the product code and total number of that product code ordered
#from the orderdetails table. Return only the rows that have more than
#1000 ordered. You will need to learn about the HAVING keyword(Google MySQL HAVING)
#it is very similar to the WHERE keyword but works with aggregate functions
#10 pts
select productCode, SUM(quantityOrdered) from orderdetails group by productCode having SUM(quantityOrdered) > 1000;

#Select the firstname, lastname and email of employees who are in offices located in
#the state of 'NY'
#10 pts
select firstname, lastname, email from employees where officeCode = (select officeCode from offices where state = 'NY');

#Select the customerName of customers who ordered at least 10 items in the
#'planes' productLine. Warning: this is probably the hardest query here and you will need
#to use the HAVING keyword
#20 pts
select c.customerName from customers as c
INNER JOIN orders AS o ON o.customerNumber = c.customerNumber
INNER JOIN orderdetails AS od ON od.orderNumber = o.orderNumber
INNER JOIN products AS p ON p.productCode = od.productCode

GROUP BY c.customerName
HAVING COUNT(p.productLine = 'planes') >= 10