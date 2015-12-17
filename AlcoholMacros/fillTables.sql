SELECT b.name, b.parent_company, cs.company_size, r.city, r.country FROM region r 
INNER JOIN brand b ON r.id = b.region_id 
INNER JOIN company_size cs ON b.company_size_id = cs.id 
ORDER BY name;

SELECT e.est_name, r.city, r.country, tmp.type, pr.price_range FROM region r 
INNER JOIN est_region er ON r.id = er.region_id 
INNER JOIN est e ON er.est_id = e.id
INNER JOIN
(SELECT et.type, e.id, e.est_price_range_id FROM est_type et
INNER JOIN est e ON et.id = e.type_id)
AS tmp ON e.id = tmp.id 
INNER JOIN est_price_range pr ON tmp.est_price_range_id = pr.id 
ORDER BY est_name;

SELECT g.name, m.material_type, g.size FROM glassware g
INNER JOIN material m ON g.material_id = m.id;

INSERT INTO glassware (name, size, material_id)
VALUES (?,?,(SELECT id FROM material WHERE material_type=?));

INSERT INTO region (city, state_country)
VALUES (?,?);

INSERT INTO brand (name, company_size_id, region_id, parent_company)
VALUES (?,(SELECT id FROM company_size WHERE company_size = ?),(SELECT id FROM region WHERE city= ? AND state_country= ?), ?);

INSERT INTO drink (name, drink_type_id, carbs, protein, fat, alcohol, proof, brand_id, serving_size)
VALUES (?,(SELECT id FROM drink_type WHERE drink_type = ?), ?, ?, ?, ?, ?, (SELECT id FROM brand WHERE brand = ?), ?);

INSERT INTO est (est_name,type_id,est_price_range_id)
VALUES (?,(SELECT id FROM est_type WHERE type = ?), (SELECT id FROM est_price_range WHERE price_range = ?));

INSERT INTO est_region (est_id, region_id)
VALUES ((SELECT id FROM region WHERE city = ? AND country = ?),?);

INSERT INTO drink_glassware (drink_id, glassware_id)
VALUES ((SELECT id FROM drink WHERE name = ?), (SELECT id FROM glassware WHERE name = ?));

SELECT e.est_name FROM est e 
INNER JOIN est_region er ON e.id = er.est_id 
INNER JOIN region r ON er.region_id = r.id 
WHERE city = ? AND state_country = ?;

SELECT e.est_name, r.city, r.state_country FROM est e
INNER JOIN est_region er ON e.id = er.est_id 
INNER JOIN region r ON er.region_id = r.id; 

SELECT b.name, d.name, dt.drink_type, d.carbs, d.protein, d.fat, d.proof, d.serving_size FROM brand b
INNER JOIN drink d ON b.id = d.brand_id
INNER JOIN drink_type dt ON d.drink_type_id = dt.id
ORDER BY b.name;

INSERT INTO est_glassware (est_id, glassware_id)
VALUES ((SELECT id FROM est WHERE est_name = ? AND city = ? AND state_country = ?),(SELECT id FROM glassware WHERE name = ?)); 

INSERT INTO est_drink (est_id, drink_id) 
VALUES (
	(SELECT e.id FROM est e 
		INNER JOIN est_region er ON e.id = er.est_id 
		INNER JOIN region r ON er.region_id = r.id 
		WHERE e.est_name = ? AND r.city = ? AND r.state_country = ?),
	(SELECT d.id FROM drink d 
		INNER JOIN brand b ON d.brand_id = b.id
		WHERE d.name = ? AND b.name = ?));

SELECT d.name, d.proof, d.carbs, d.protein, d.fat FROM drink d
INNER JOIN brand b ON d.brand_id = b.id
WHERE b.name = ? AND d.name LIKE ?  