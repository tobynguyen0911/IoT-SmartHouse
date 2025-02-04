from flask import Flask, jsonify, request
from flask_pymongo import PyMongo
from flask_swagger import swagger
import uuid
from swagger_ui import api_doc
from bson import json_util

def create_app():
    app = Flask(__name__)
    app.config["MONGO_URI"] = "mongodb://root:pass@db:27017/homeAutomation?authSource=admin"
    api_doc(app, config_url='http://localhost:5000/spec.json', url_prefix='/api/doc', title='API doc')
    return app

def create_mongo(app):
    return PyMongo(app)

app = create_app()
mongo = create_mongo(app)

def create_or_return_device(device: dict, controller_id):
  device["controller_id"] = controller_id
  device["device_id"] = uuid.uuid4().hex
  ret = mongo.db.devices.insert_one(device).inserted_id
  return device


# Controller Event Notification
@app.route("/api/devices/<device_id>/events", methods=["GET"])
def get_device_events(device_id):
    """
    Get pending events for a specific controller.
    ---
    tags:
      - Controller Event Notification
    parameters:
      - name: controller_id
        in: path
        type: string
        required: true
    responses:
      200:
        description: Events retrieved successfully
    """
    # Mocked response for demonstration purpose
    event_example = [
        {
            "Type": "Action",
            "UUID": "EV2",
            "Destination": "Device Address",
            "Origin": "Server",
            "Completed": False,
            "Content": {
                "Device": "UUID0",
                "Function": {
                    "Name": "Set",
                    "Args": {"State": False}
                }
            }
        }
    ]
    # Query the database for events with Completed == False for the specified controller_id
    pending_events = list(mongo.db.events.find({"device_id": device_id}))

    mongo.db.events.delete_many({"device_id": device_id})

    # Return response with pending events
    return json_util.dumps(pending_events)


# Device Management
@app.route("/api/controllers/<controller_id>/devices", methods=["GET"])
def get_devices_by_controller(controller_id):
    """
    Get information about all devices with a given controller
    ---
    tags:
      - Device Management
    responses:
      200:
        description: Device information retrieved successfully
    """
    devices = list(mongo.db.devices.find({"controller_id": controller_id}))
    return json_util.dumps(devices)


@app.route("/api/events", methods=["GET"])
def get_all_events():
    pending_events = list(mongo.db.events.find({}))

    # Return response with pending events
    return json_util.dumps(pending_events)


# Controller Event Notification
@app.route("/api/controllers/<controller_id>/events", methods=["GET"])
def get_events_for_controller(controller_id):
    """
    Get pending events for a specific controller.
    ---
    tags:
      - Controller Event Notification
    parameters:
      - name: controller_id
        in: path
        type: string
        required: true
    responses:
      200:
        description: Events retrieved successfully
    """
    # Query the database for events with Completed == False for the specified controller_id
    pending_events = list(mongo.db.events.find({"controller_id": int(controller_id)}))

    mongo.db.events.delete_many({"controller_id": int(controller_id)})

    # Return response with pending events
    return json_util.dumps(pending_events)


# Controller Event Notification
@app.route("/api/devices/<device_id>/events", methods=["POST"])
def add_controller_events(device_id):
    """
    Add pending event for a specific controller.
    """
    data = request.get_json(force=True)
    mongo.db.events.insert_one(data)
    return json_util.dumps({"Result": "Success"})


# Device State Update
@app.route("/api/devices/<device_id>", methods=["POST"])
def update_device(device_id):
    """
    Update the state of a device.
    ---
    tags:
      - Device State Update
    parameters:
      - name: device_id
        in: path
        type: string
        required: true
      - name: body
        in: body
        required: true
        schema:
          type: object
          properties:
            Controller:
              type: object
              properties:
                UUID:
                  type: string
                Devices:
                  type: array
                  items:
                    type: object
                    properties:
                      local_id:
                        type: string
                      UUID:
                        type: string
                      driver_id:
                        type: integer
                      state:
                        type: object  # Assuming state is an object
    responses:
      200:
        description: Device state updated successfully
    """
    data = request.get_json(force=True)
    if "_id" in data.keys():
      del data["_id"]
    result = mongo.db.devices.update_one({"device_id": device_id}, {"$set": data})
    return json_util.dumps({"Controller": {"id": str(result.modified_count)}})

@app.route("/api/devices/<device_id>", methods=["GET"])
def get_device(device_id):
    """
    Get information about a specific device.
    ---
    tags:
      - Device Management
    parameters:
      - name: device_id
        in: path
        type: string
        required: true
    responses:
      200:
        description: Device information retrieved successfully
      404:
        description: Device not found
    """
    device = mongo.db.devices.find_one_or_404({"device_id": device_id})
    return json_util.dumps(device)


# Controller Management
@app.route("/api/controllers", methods=["POST"])
def create_controller():
    """
    Create a new controller.
    ---
    tags:
      - Controller Management
    parameters:
      - name: body
        in: body
        required: true
        schema:
          type: object
          properties:
            Controller:
              type: object
              properties:
                Devices:
                  type: array
                  items:
                    type: object
                    properties:
                      local_id:
                        type: string
                      UUID:
                        type: string
                      driver_id:
                        type: integer
                local_id:
                    type: string
    responses:
      200:
        description: Controller created successfully
    """
    print("Request received")
    print(request.data)

    data = request.get_json(force=True)

    # First check if a controller with the same local_id exists in the database
    existing_controller = mongo.db.controllers.find_one({"local_id": data["local_id"]})
    

    if existing_controller:
        # Controller already exists, return its information
        return json_util.dumps(existing_controller)

    devices = [create_or_return_device(device, data["local_id"]) for device in data.get('devices')]
    data["devices"] = devices

    # Insert the new controller into the database
    controller_id = mongo.db.controllers.insert_one(data).inserted_id

    # Return response with generated UUID
    return json_util.dumps({"controller_id": str(controller_id), **data})


@app.route("/api/controllers", methods=["GET"])
def get_controllers():
    """
    Get information about all controllers.
    ---
    tags:
      - Controller Management
    responses:
      200:
        description: Controller information retrieved successfully
    """
    mongo.db
    controllers = list(mongo.db.controllers.find({}))
    return json_util.dumps(controllers)


# Device Management
@app.route("/api/devices", methods=["POST"])
def post_devices():
    """
    Set multiple devices simultaneously
    ---
    tags:
      - Device Management
    responses:
      200:
        description: Device information retrieved successfully
    """
    data = request.json
    for device in data:
      print(device)
      device.pop("_id", None)
      result = mongo.db.devices.update_one({"device_id": device["device_id"] }, {"$set": device})
    return json_util.dumps({"Result": "Success"})

# Device Management
@app.route("/api/devices", methods=["GET"])
def get_devices():
    """
    Get information about all devices.
    ---
    tags:
      - Device Management
    responses:
      200:
        description: Device information retrieved successfully
    """
    #data = request.get_json(force=True)
    #result = mongo.db.devices.update_one({"_id": }, {"$set": data["Controller"]["Devices"][0]})
    #return jsonify({"Controller": {"id": str(result.modified_count)}})
    devices_list= list(mongo.db.devices.find({}))
    return json_util.dumps(devices_list)


# Controller Event Notification
@app.route("/api", methods=["DELETE"])
def delete_records():
    mongo.db.events.delete_many({})
    mongo.db.controllers.delete_many({})
    mongo.db.devices.delete_many({})
    return json_util.dumps({"Result": "Success"})
 

@app.route("/spec.json")
def spec():
    swag = swagger(app)
    swag['info']['version'] = "1.0"
    swag['info']['title'] = "Home Automation API"
    return jsonify(swag)

if __name__ == "__main__":
    app.run(debug=True)
