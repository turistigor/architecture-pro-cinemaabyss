from os import environ
from typing import Generator

from proxy.routing.distributor import Distributor
from proxy.routing.service_distributor import ServiceMultiDistributor, ServiceDistributor
from proxy.routing.services import ServiceName

monolith_url = environ.get('MONOLITH_URL', 'http://monolith:8080')
movies_url = environ.get('MOVIES_SERVICE_URL', 'http://movies-service:8081')
events_url = environ.get('EVENTS_SERVICE_URL', 'http://events-service:8082')

gradual_migration = environ.get('GRADUAL_MIGRATION', True)
if gradual_migration == 'false':
    gradual_migration = False
elif gradual_migration == 'true':
    gradual_migration = True

ratio = float(environ.get('MOVIES_MIGRATION_PERCENT', 50)) / 100

if gradual_migration is True:
    movies_router = ServiceMultiDistributor(
        ratio=ratio,
        route=monolith_url,
        add_route = movies_url,
    )
else:
    movies_router = ServiceDistributor(movies_url)

users_router = ServiceDistributor(route=monolith_url)
events_router = ServiceDistributor(route=events_url)
subs_router = ServiceDistributor(route=monolith_url)
pays_router = ServiceDistributor(route=monolith_url)

routes_map = {
    ServiceName.MOVIES: movies_router,
    ServiceName.USERS: users_router,
    ServiceName.EVENTS: events_router,
    ServiceName.SUBS: subs_router,
    ServiceName.PAYMENTS: pays_router,
}


def get_distributor() -> Generator[Distributor, None, None]:
    yield Distributor(routes_map=routes_map)
