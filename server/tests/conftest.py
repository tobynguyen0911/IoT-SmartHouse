import pytest
import sys
import os

## Setup path for all tests
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))

from src.app import app as src_app

@pytest.fixture
def app():
    return src_app

@pytest.fixture
def client(app):
    return app.test_client()

