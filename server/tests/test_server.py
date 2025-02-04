import requests
from bson import json_util
from test_utils import make_request

def test_controllers(client):
    r = make_request(client, endpoint="/controllers")
    loaded = json_util.loads(r.data)
    assert len(loaded["Controllers"]) > 0   