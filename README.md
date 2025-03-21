# StoreClustering-SalesInsights
"A C++ program that uses K-Means clustering to analyze store sales performance, predict future trends, and visualize data with ASCII graphs."
Store Clustering & Sales Analysis System

📌 Overview

This project is a C++-based system that applies K-Means clustering to group stores based on location and sales performance. It provides graphical insights, sales forecasting, and performance ranking of stores based on profitability and growth rate. If store or sales data files are missing, the program automatically generates new data, ensuring smooth execution.

🛠 Features

✅ K-Means Clustering – Automatically groups stores into clusters and sub-clusters based on location & sales.✅ Automatic Data Generation – If store or sales data files are missing, the program creates random store and sales data.✅ Sales Forecasting – Predicts future sales using 6-month & 12-month models.✅ Performance Ranking – Sorts stores by profit, sales volume, & growth rate.✅ Graphical Representation – ASCII bar charts for sales trends & cluster performance.✅ File-Based Data Storage – Saves and loads store & sales data from files.

📂 Project Structure

📊 How the Program Works
1️⃣ Checks for Store & Sales Data Files – If missing, it generates new data automatically.
2️⃣ Clusters Stores by Location & Performance – Uses K-Means clustering.
3️⃣ Analyzes Sales Trends – Computes trends and displays ASCII graphs.
4️⃣ Predicts Future Sales – Uses a forecasting model to estimate future revenue.
5️⃣ Sorts & Ranks Stores – Identifies top and bottom-performing stores based on profit, sales, and growth.
6️⃣ Visualizes Cluster Performance – Graphs showing profit trends for clusters and sub-clusters.

🔄 Automatic Data Generation
If the required store or sales files are missing, the program:✔ Randomly generates store locations & sales data✔ Saves the generated data to new files✔ Ensures smooth execution without manual input

🚀 To-Do & Future Enhancements

✅ Improve graph scaling for better accuracy.

✅ Optimize sales forecasting algorithm using machine learning.

🔄 Implement database storage (SQLite, MySQL) instead of text files.

🔄 Compare K-Means with DBSCAN for better clustering.

🔄 Convert to a GUI-based application using Qt or Python integration.
