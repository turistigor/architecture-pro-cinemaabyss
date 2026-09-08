from proxy.api.gateway import movies_router
from proxy.api.healthcheck import health_router

__all__ = (
    'health_router',
    'movies_router',
)
