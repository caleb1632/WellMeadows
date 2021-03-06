CREATE TABLE WARD_INFO(
WardNumber INTEGER PRIMARY KEY,
WardName VARCHAR(25),
WardLocation VARCHAR(25),
NumberOfBeds INTEGER,
PhoneExtension INTEGER
)ENGINE = INNODB;

CREATE TABLE POSITION_NEEDED(
PositionID INTEGER PRIMARY KEY,

Position VARCHAR(35)
)ENGINE = INNODB;

CREATE TABLE WARD_STAFF(
WardNumber INTEGER PRIMARY KEY,
PositionID INTEGER REFERENCES POSITION_INFO(PositionID)
)ENGINE = INNODB;

CREATE TABLE WARD_SHIFTS(
PositionID INTEGER REFERENCES WARD_STAFF(PositionID),
WardNumber INTEGER REFERENCES WARD_STAFF(WardNumber),
ShiftID INTEGER,
PRIMARY KEY(PositionID, WardNumber)
)ENGINE = INNODB;

CREATE TABLE REQUIRED_STAFF(
PositionID INTEGER REFERENCES WARD_SHIFTS(PositionID),
ShiftID INTEGER REFERENCES WARD_SHIFTS(ShiftID),
StaffNeeded INTEGER,
PRIMARY KEY(PositionID, ShiftID)
)ENGINE = INNODB;

CREATE TABLE WARD_BEDS(
WardNumber INTEGER REFERENCES WARD_INFO(WardNumber),
BedNumber INTEGER,
PRIMARY KEY(WardNumber)
)ENGINE = INNODB;

CREATE TABLE STAFF_ON_WARD(
WardNumber INTEGER REFERENCES WARD_INFO(WardNumber),
StaffNumber INTEGER,
PositionID INTEGER REFERENCES REQUIRED_STAFF(PositionID),
PRIMARY KEY(WardNumber, StaffNumber)
)ENGINE = INNODB;

CREATE TABLE WARD_REQUISITION(
WardNumber INTEGER REFERENCES WARD_INFO(WardNumber),
StaffNumber INTEGER REFERENCES STAFF_ON_WARD(StaffNumber),
ReqNumber INTEGER,
ItemDrugNumber INTEGER,
ItemName VARCHAR(50),
QuantityRequired INTEGER,
DateOrdered DATE,
DateRecieved DATE,
PRIMARY KEY(WardNumber, StaffNumber)
)ENGINE = INNODB;

CREATE TABLE SUPPLIES_USED(
ItemNumber INTEGER,
WardNumber INTEGER REFERENCES WARD_INFO(WardNumber),
QuantityUsed INTEGER,
DateUsed DATE,
PRIMARY KEY(ItemNumber, WardNumber)
)ENGINE = INNODB;