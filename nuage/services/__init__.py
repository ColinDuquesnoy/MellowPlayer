"""
This package contains the available cloud music services
"""
from nuage.services.grooveshark import GroovesharkService


#: Lists the available cloud music services
AVAILABLE_SERVICES = [
    GroovesharkService,
]
