from proxy.routing.service_distributor import IServiceDistributor
from proxy.routing.services import ServiceName


class Distributor:
    def __init__ (self, routes_map: dict[ServiceName, IServiceDistributor]):
        self._routes_map = routes_map
    
    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, 'instance'):
            cls.instance = super(cls, Distributor).__new__(cls)
        return cls.instance

    def get_route(self, url: str) -> str:
        name = get_service_name(url)
        service_router = self._routes_map[name]
        return service_router.get_route()


def get_service_name(url: str) -> ServiceName:
    parts = url.split('/')
    try:
        name_index = parts.index('api') + 1
    except ValueError:
        raise ValueError()

    if name_index == len(parts):
        raise ValueError(
            f'Invalid url: there is no service name {url}'
        )

    name = parts[name_index]
    return ServiceName(name)
