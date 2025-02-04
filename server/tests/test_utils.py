import pytest
import requests

def make_request(client, body=None, endpoint="", method="GET", base_url=""):
    """
    Abstract away making requests

    """

    if method == 'GET':
        return client.get(endpoint)
    elif method == 'POST':
        return client.post(endpoint, body)
    elif method == 'PUT':
        pass
