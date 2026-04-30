CREATE DATABASE airFareDB;
USE airFareDB;

CREATE TABLE airline(
	id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(64),
    country VARCHAR(64)
);

CREATE TABLE airplane(
	id INT PRIMARY KEY AUTO_INCREMENT,
    airlineID INT,
    model VARCHAR(32),
    totalRows INT, 
    totalColumns INT,
    FOREIGN KEY(airlineID) REFERENCES airline(id)
);

CREATE TABLE flight(
	id INT PRIMARY KEY AUTO_INCREMENT,
    airlineID INT,
    airplaneID INT,
    source VARCHAR(32),
    destination VARCHAR(32), 
    dateOfFlight VARCHAR(16),
    takeOffTime VARCHAR(16),
    FOREIGN KEY(airlineID) REFERENCES airline(id),
    FOREIGN KEY(airplaneID) REFERENCES airplane(id)
);

CREATE TABLE passenger(
	id INT PRIMARY KEY AUTO_INCREMENT,
    cnic VARCHAR(13) UNIQUE CHECK(length(cnic) = 13),
    name VARCHAR(32),
    contact VARCHAR(16),
    lastFlight VARCHAR(16)
    );
    
CREATE TABLE ticket(
	id INT PRIMARY KEY AUTO_INCREMENT,
    flightID INT,
    passengerID INT,
    seatNo INT,
    price INT,
    dateOfBooking DATETIME DEFAULT CURRENT_TIMESTAMP,
    status VARCHAR(16) DEFAULT 'CONFIRMED',
    FOREIGN KEY(flightID) REFERENCES flight(id),
    FOREIGN KEY(passengerID) REFERENCES passenger(id),
    CONSTRAINT uq_flight_seat UNIQUE(flightID, seatNo)
);
    
SELECT * FROM flight;
SELECT * FROM passenger;
SELECT * FROM ticket;

INSERT INTO airline(title, country) VALUES("Emirates", "UAE");
INSERT INTO airline(title, country) VALUES("SkyAir", "USA");
INSERT INTO airline(title, country) VALUES("PIA", "PAK");
SELECT * FROM airline;

INSERT INTO airplane(airlineID, model, totalRows, totalColumns) VALUES(1, "Boeng-707", 12, 6);
INSERT INTO airplane(airlineID, model, totalRows, totalColumns) VALUES(1, "Boeng-705", 14, 6);
INSERT INTO airplane(airlineID, model, totalRows, totalColumns) VALUES(1, "Boeng-703", 16, 6);
SELECT * FROM airplane;