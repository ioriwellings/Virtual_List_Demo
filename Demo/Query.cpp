//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Query.h"

namespace Query {

    LPCWSTR const pszOrdersQuery = 
L"SELECT "      
    L"Orders.[Order ID], Orders.[Ship Name], Orders.[Ship Address], Orders.[Ship City], "
    L"Orders.[Ship Region], Orders.[Ship Postal Code], Orders.[Ship Country], " 
    L"Orders.[Ship Via], Orders.[Order Date], Orders.[Required Date], "
    L"Orders.[Shipped Date], "
    L"Customers.[Company Name] AS [Customer Company Name], Customers.[Contact Name] AS [Customer Contact Name], "
    L"Customers.[Contact Title] AS [Customer Contact Title], Customers.Address AS [Customer Address], " 
    L"Customers.City AS [Customer City], Customers.Region AS [Customer Region], Customers.[Postal Code] AS [Customer Postal Code], " 
    L"Customers.Country AS [Customer Country], Customers.Phone AS [Customer Phone], Customers.Fax AS [Customer Fax], " 
    L"Employees.[Last Name] AS [Employee Last Name], Employees.[First Name] AS [Employee First Name], "
    L"[Order Details].[Unit Price], [Order Details].Quantity, [Order Details].Discount, "
    L"Products.[Product Name], Products.[English Name], Products.[Quantity Per Unit], "
    L"Products.[Unit Price] AS [Product Unit Price], Products.[Units In Stock], "
    L"Products.[Units On Order], Products.[Reorder Level], "
    L"Suppliers.[Company Name] AS [Supplier Company Name], "
    L"Categories.[Category Name], "
    L"Shippers.[Company Name] AS [Shipper Company Name] "
L"FROM "
    L"Orders INNER JOIN "
    L"Customers ON Orders.[Customer ID] = Customers.[Customer ID] INNER JOIN "
    L"Employees ON Orders.[Employee ID] = Employees.[Employee ID] INNER JOIN "
    L"[Order Details] ON Orders.[Order ID] = [Order Details].[Order ID] INNER JOIN "
    L"Products ON [Order Details].[Product ID] = Products.[Product ID] INNER JOIN "
    L"Suppliers ON Products.[Supplier ID] = Suppliers.[Supplier ID] INNER JOIN "
    L"Categories ON Products.[Category ID] = Categories.[Category ID] INNER JOIN "
    L"Shippers ON Orders.[Ship Via] = Shippers.[Shipper ID] ";

} // namespace Query