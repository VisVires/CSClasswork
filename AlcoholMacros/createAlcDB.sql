#Create drink_type table
CREATE TABLE drink_type(
id INT NOT NULL AUTO_INCREMENT,
drink_type VARCHAR(255) NOT NULL,
PRIMARY KEY (id)
) ENGINE=InnoDB;

#create material table
CREATE TABLE material(
id INT NOT NULL AUTO_INCREMENT,
material_type VARCHAR(255) NOT NULL,
PRIMARY KEY (id)
) ENGINE=InnoDB;

#Create establishment price range table
CREATE TABLE est_price_range(
id INT NOT NULL AUTO_INCREMENT,
price_range VARCHAR(255) NOT NULL,
PRIMARY KEY (id)
) ENGINE=InnoDB;

#Create establishment type table
CREATE TABLE est_type(
id INT NOT NULL AUTO_INCREMENT,
type VARCHAR(255) NOT NULL,
PRIMARY KEY (id)
) ENGINE=InnoDB;
 
#Create establishment table
CREATE TABLE est(
id INT NOT NULL AUTO_INCREMENT,
est_name VARCHAR(255) NOT NULL,
type_id INT NOT NULL,
est_price_range_id INT NOT NULL,
region_id INT NOT NULL,
PRIMARY KEY (id),
FOREIGN KEY (type_id) REFERENCES est_type (id),
FOREIGN KEY (est_price_range_id) REFERENCES est_price_range (id),
FOREIGN KEY (region_id) REFERENCES region (id) 
) ENGINE = InnoDB;

#Create region table
CREATE TABLE region(
id INT NOT NULL AUTO_INCREMENT,
city VARCHAR(255) NOT NULL,
state_country VARCHAR (255) NOT NULL,
PRIMARY KEY (id),
UNIQUE KEY(city, state_country)
) ENGINE=InnoDB;

#Create company size table
CREATE TABLE company_size(
id INT NOT NULL AUTO_INCREMENT,
company_size VARCHAR(255) NOT NULL,
PRIMARY KEY(id)
) ENGINE=InnoDB; 


#Create establishment region table
CREATE TABLE est_region(
est_id INT NOT NULL,
region_id INT NOT NULL,
FOREIGN KEY (est_id) REFERENCES est(id),
FOREIGN KEY (region_id) REFERENCES region(id)
)ENGINE=InnoDB;

#Create brand table
CREATE TABLE brand(
id INT NOT NULL AUTO_INCREMENT,
name VARCHAR(255) NOT NULL,
parent_company VARCHAR(255),
company_size_id INT,
region_id INT NOT NULL,
PRIMARY KEY(id),
FOREIGN KEY (company_size_id) REFERENCES company_size(id),
FOREIGN KEY (region_id) REFERENCES region(id)
)ENGINE=InnoDB;

#Create glassware table
CREATE TABLE glassware(
id INT NOT NULL AUTO_INCREMENT,
name VARCHAR(255) NOT NULL,
material_id INT NOT NULL,
size DECIMAL(4,2) UNSIGNED,
PRIMARY KEY(id),
FOREIGN KEY (material_id) REFERENCES material(id),
UNIQUE KEY (name, material_id, size)
) ENGINE=InnoDB;

#Create establishment glassware table
CREATE TABLE est_glassware(
est_id INT NOT NULL,
glassware_id INT NOT NULL,
FOREIGN KEY (est_id) REFERENCES est(id),
FOREIGN KEY (glassware_id) REFERENCES glassware(id)
)ENGINE=InnoDB;

#Create drink table
CREATE TABLE drink(
id INT NOT NULL AUTO_INCREMENT,
name VARCHAR(255) NOT NULL,
drink_type_id INT NOT NULL,
carbs DECIMAL(4,2) UNSIGNED ZEROFILL NOT NULL DEFAULT '0.0',
protein DECIMAL(4,2) UNSIGNED ZEROFILL NOT NULL DEFAULT '0.0',
fat DECIMAL(4,2) UNSIGNED ZEROFILL NOT NULL DEFAULT '0.0',
alcohol BOOL NOT NULL,
proof DECIMAL(4,2) UNSIGNED ZEROFILL NOT NULL DEFAULT '0.0',
brand_id INT NOT NULL,
serving_size DECIMAL(4,2) UNSIGNED ZEROFILL NOT NULL DEFAULT '0.0',
PRIMARY KEY (id),
FOREIGN KEY (drink_type_id) REFERENCES drink_type (id),
FOREIGN KEY (brand_id) REFERENCES brand (id)
)ENGINE=InnoDB;

#Create establishment drink table
CREATE TABLE est_drink(
drink_id INT NOT NULL,
est_id INT NOT NULL,
FOREIGN KEY (drink_id) REFERENCES drink (id),
FOREIGN KEY (est_id) REFERENCES est (id)
) ENGINE=InnoDB;

#Create drink glassware table
CREATE TABLE drink_glassware(
drink_id INT NOT NULL,
glassware_id INT NOT NULL,
FOREIGN KEY (drink_id) REFERENCES drink (id),
FOREIGN KEY (glassware_id) REFERENCES glassware (id)
) ENGINE=InnoDB;
