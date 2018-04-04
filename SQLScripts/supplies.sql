CREATE TABLE ITEM_ORDER(
ItemNumber INTEGER REFERENCES ITEM_INFO(ItemNumber),
ReOrderLevel INTEGER NOT NULL,
QuantityOnHand INTEGER NOT NULL REFERENCES ITEM_INFO(QuantityOnHand)
)ENGINE = INNODB;

CREATE TABLE SUPPLIES_USED(
ItemNumber INTEGER REFERENCES ITEM_INFO(ItemNumber),
WardNumber INTEGER REFERENCES WARD_INFO(WardNumber),
QuantityUsed INTEGER NOT NULL,
THE_DATE DATE
)ENGINE = INNODB;

CREATE TABLE SUPPLIER_PHONE_NUMBER(
SupplierNumber INTEGER REFERENCES SUPPLIERS(SupplierNumber),
PhoneNumber VARCHAR(25),
FaxNumber VARCHAR(25),
PRIMARY KEY(SupplierNumber)
)ENGINE = INNODB;

CREATE TABLE SUPPLIER_ADDRESS(
SupplierNumber INTEGER REFERENCES SUPPLIERS(SupplierNumber),
State VARCHAR(25) NOT NULL,
City VARCHAR(50) NOT NULL,
StreetNumber INTEGER NOT NULL,
Street VARCHAR(50) NOT NULL,
PRIMARY KEY(SupplierNumber)
)ENGINE = INNODB;

CREATE TABLE ITEM_INFO(
ItemNumber INTEGER PRIMARY KEY,
ItemName VARCHAR(25),
ItemDescription VARCHAR(50),
QuantityOnHand INTEGER NOT NULL
)ENGINE = INNODB;

CREATE TABLE SUPPLIERS(
SupplierNumber INTEGER PRIMARY KEY,
SupplierName VARCHAR(50)
)ENGINE = INNODB;

