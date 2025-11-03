# ALLOWED_ORIGINS=http://localhost:3000,http://192.168.20.38:3000,http://a3510377.github.io/Elder-Care-App
# PORT=8000

# # DB_CONN_STRING="mongodb+srv://githun:<password>@sandbox.jadwj.mongodb.net"
# DB_CONN_STRING="mongodb://192.168.20.2:27017"
# DATABASE_USERNAME=<username>
# DATABASE_PASSWORD=<password>
# DB_NAME="elder-care-app"
# NOTIFY_TOKEN=


import pymongo
from bson.objectid import ObjectId

myclient = pymongo.MongoClient("mongodb://<username>:<password>@192.168.20.2:27017")
db = myclient["elder-care-app"]
users = db["users"]

user_data = [
    {
        "_id": ObjectId("65f44a5625490c75aef1d00e"),
        "name": "馬仁義",
        "age": 88,
        "phone": "06-7124586",
        "gender": 0,
        "remark": "三高慢性病，行動不便",
        "address": "臺南市善化區仁義里70號",
        "device": [
            ObjectId("65f58bc225490c75aef1d029"),
            ObjectId("661a1f85b93bf5a909e3fa2b"),
        ],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a6725490c75aef1d010"),
        "name": "施孝文",
        "age": 76,
        "phone": "0928555123",
        "gender": 0,
        "remark": "失智，三高慢性病、可無輔具行走",
        "address": "臺南市安定區孝文里60號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a6c25490c75aef1d012"),
        "name": "柯中和",
        "age": 77,
        "phone": "0936258741",
        "gender": 0,
        "remark": "三高慢性病、可無輔具行走",
        "address": "臺南市官田區中和里50號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a7025490c75aef1d014"),
        "name": "林美如",
        "age": 72,
        "phone": "06-5728129",
        "gender": 1,
        "remark": "有心臟病、氣喘史、可無輔具行走",
        "address": "臺南市麻豆區如意里35號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a7325490c75aef1d016"),
        "name": "宋小芳",
        "age": 66,
        "phone": "06-7458268",
        "gender": 1,
        "remark": "視力不良，行動不便",
        "address": "臺南市學甲區美芳里25號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a7725490c75aef1d018"),
        "name": "朱明通",
        "age": 65,
        "phone": "06-7941582",
        "gender": 0,
        "remark": "三高慢性病、可無輔具行走",
        "address": "臺南市將軍區明通里120號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a7a25490c75aef1d01a"),
        "name": "石阿文",
        "age": 82,
        "phone": "06-7561245",
        "gender": 0,
        "remark": "失智，三高慢性病、可無輔具行走",
        "address": "臺南市北門區文新里110號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a7f25490c75aef1d01c"),
        "name": "方如花",
        "age": 76,
        "phone": "0925664781",
        "gender": 1,
        "remark": "癌症二期，行動不便",
        "address": "臺南市西港區如花里200號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a8225490c75aef1d01e"),
        "name": "王小明",
        "age": 78,
        "phone": "0912126545",
        "gender": 0,
        "remark": "中風過，行動不便",
        "address": "臺南市七股區小明里20號",
        "device": [],
        "__v": 0,
    },
    {
        "_id": ObjectId("65f44a8b25490c75aef1d020"),
        "name": "丁大同",
        "age": 80,
        "phone": "06-7225566",
        "gender": 0,
        "remark": "三高慢性病、可無輔具行走",
        "address": "臺南市佳里區大同里100號",
        "device": [],
        "__v": 0,
    },
]

users.delete_many({})
users.insert_many(user_data)

device_data = [
    {"_id": ObjectId("65f58bc225490c75aef1d029"), "type": 0, "__v": 0},
    {"_id": ObjectId("661a1f85b93bf5a909e3fa2b"), "type": 1, "__v": 0},
]

devices = db["devices"]
devices.delete_many({})
devices.insert_many(device_data)

data = {
    "co": 0,
    "co2": 0,
    "pm2_5": 0,
    "warn": {
        "co": True,
        "co2": True,
        "pm2_5": True,
    },
}
