#Insert Material Types
INSERT INTO material (material_type)
VALUES ('GLASS'),('PLASTIC'),('METAL'),('WOOD'),('OTHER');

#Insert Company Sizes into company_size
INSERT INTO company_size (company_size)
VALUES ('SMALL (1-20 EMPLOYEES)'),('MEDIUM (20-200 EMPLOYEES)'),('NATIONAL (200-1000 EMPLOYEES)'),('GLOBAL (1000+ EMPLOYEES)');

#Insert Drink Type Into drink_type table
INSERT INTO drink_type (drink_type)
VALUES ('BEER'),('WINE'),('LIQUOR'),('OTHER');

#Insert Establishment Types in est_type table
INSERT INTO est_type (type)
VALUES ('RESTAURANT/BAR'),('DANCE CLUB'),('BREWERY'),('SPORTS VENUE'),('OTHER');

#Insert price ranges into est_price_range table 
INSERT INTO est_price_range (price_range)
VALUES ('$3 OR LESS PER DRINK'),('$3-5 PER DRINK'),('$5-9 PER DRINK'),('$9+ PER DRINK');

#Insert regions into region table
INSERT INTO region (city, state_country)
VALUES ('Bruxelles', 'Belgium'), ('London','England'), ('St. Louis', 'Missouri'), ('Zoeterwoude','Netherlands'),('Copenhagen','DENMARK')
,('Paris','France'), ('Bangalore','Karnataka','India'), ('Hamilton','Bermuda'), ('Victor','New York'), ('Modesto','California') 
, ('Livermore','California'), ('Southbank','Melbourne','Australia'), ('Deerfield','Illinois'), ('Denver','Colorado'), ('Montreal','Canada')
, ('Edinburgh','Scotland'), ('Hong Kong','China'),('Seattle','Washington'), ('New York','New York');

INSERT INTO brand (name, company_size_id, region_id, parent_company)
VALUES ('Budweiser',4,(SELECT id FROM region WHERE city='St. Louis' AND country='USA'),'Anheuser-Busch'), 
('Smirnoff',4,(SELECT id FROM region WHERE city='London' AND country='England'),'Diageo'),
('Coors',4,(SELECT id FROM region WHERE city='Denver' AND country='USA'),'Molson Coors'),
('Bacardi',4,(SELECT id FROM region WHERE city='Hamilton' AND country='Bermuda'),'Bacardi'),
('Blue Moon',4,(SELECT id FROM region WHERE city='London' AND country='England'),'SABMiller'),
('Heineken',4,(SELECT id FROM region WHERE city='Zoeterwoude' AND country='Netherlands'),'Heineken'),
('Johnny Walker',4,(SELECT id FROM region WHERE city='London' AND country='England'),'Diageo'),
('Guinness',4,(SELECT id FROM region WHERE city='London' AND country='England'),'Diageo'),
('Absolut',4,(SELECT id FROM region WHERE city='Paris' AND country='France'),'Pernod Richard'),
('Corona',4,(SELECT id FROM region WHERE city='Victor' AND country='USA'),'Constellation Brands');

INSERT INTO glassware (name, material_id, size)
VALUES ('Imperial Pint',(SELECT id FROM material WHERE material_type='GLASS'),20.0),
('American Pint',(SELECT id FROM material WHERE material_type='GLASS'),16.0),
('Pilsner',(SELECT id FROM material WHERE material_type='GLASS'),20.0),
('Snifter',(SELECT id FROM material WHERE material_type='GLASS'), 8.0),
('Wheat Beer Glass',(SELECT id FROM material WHERE material_type='GLASS'), NULL),
('Beer Mug',(SELECT id FROM material WHERE material_type='GLASS'), NULL),
('Martini',(SELECT id FROM material WHERE material_type='GLASS'), NULL),
('Coupe',(SELECT id FROM material WHERE material_type='GLASS'), 8.75),
('Highball',(SELECT id FROM material WHERE material_type='GLASS'),10.0),
('Lowball',(SELECT id FROM material WHERE material_type='GLASS'),6.0),
('White Wine Glass',(SELECT id FROM material WHERE material_type='GLASS'),12.0),
('Red Wine Glass',(SELECT id FROM material WHERE material_type='GLASS'),12.0),
('Champagne Flute',(SELECT id FROM material WHERE material_type='GLASS'), 6.0),
('Stemless Glass',(SELECT id FROM material WHERE material_type='GLASS'), NULL),
('Shot Glass',(SELECT id FROM material WHERE material_type='GLASS'), 1.5);