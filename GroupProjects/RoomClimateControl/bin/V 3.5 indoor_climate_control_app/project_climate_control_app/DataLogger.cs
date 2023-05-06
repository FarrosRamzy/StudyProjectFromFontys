using System;
using MongoDB.Driver;
using MongoDB.Bson;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace project_climate_control_app
{
    class DataLogger
    {
        private string MongoDBCloudAddressString = "mongodb://FizzyRamzy:ThisGroupIsAwesome@group4roomclimatesystem-shard-00-00.dajhq.mongodb.net:27017,group4roomclimatesystem-shard-00-01.dajhq.mongodb.net:27017,group4roomclimatesystem-shard-00-02.dajhq.mongodb.net:27017/myFirstDatabase?ssl=true&replicaSet=atlas-14kg58-shard-0&authSource=admin&retryWrites=true&w=majority";
        private string databaseName = "RoomClimateSystemGroup4";
        private string collectionName = "RoomClimateData";

        MongoClient mongoClient;
        IMongoDatabase mongoCloudDatabase;
        IMongoCollection<BsonDocument> mongoCloudCollection;

        /// <summary>
        /// Create new client to connect with the cloud.
        /// </summary>
        public DataLogger()
        {
            mongoClient = new MongoClient(MongoDBCloudAddressString);
            mongoCloudDatabase = mongoClient.GetDatabase(databaseName);
            mongoCloudCollection = mongoCloudDatabase.GetCollection<BsonDocument>(collectionName);
        }

        /// <summary>
        /// Upload the parameter into the cloud server database.
        /// </summary>
        /// <param name="inputData"></param>
        public void uploadData(BsonDocument inputData)
        {
            mongoCloudCollection.InsertOne(inputData);
        }

        /// <summary>
        /// Retreive data from the cloud based on the date input.
        /// </summary>
        /// <param name="startDate"></param>
        /// <returns>A list of data.</returns>
        public List<BsonDocument> downloadData(string startDate, string endDate, string startTime, string endTime)
        {
            List<BsonDocument> dataResult = new List<BsonDocument>();

            var filterBuilder = Builders<BsonDocument>.Filter;
            var fieldsBuilder = Builders<BsonDocument>.Projection;
            var fields = fieldsBuilder.Exclude("_id");
            var filter = (filterBuilder.Gte("Date", startDate) & filterBuilder.Lte("Date",endDate));
            filter &= (filterBuilder.Gte("Time", startTime) & filterBuilder.Lte("Time", endTime));
            var docs = mongoCloudCollection.Find(filter).Project<BsonDocument>(fields).ToList();

            docs.ForEach(doc => { dataResult.Add(doc); });

            return dataResult;
        }
    }
}
