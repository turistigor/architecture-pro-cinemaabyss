import math
from abc import ABC, abstractmethod


class IServiceDistributor(ABC):
    @abstractmethod
    def get_route(self) -> str:
        raise NotImplementedError


class ServiceDistributor(IServiceDistributor):
    def __init__(self, route: str):
        self._route = route

    def get_route(self) -> str:
        return self._route


class ServiceMultiDistributor(ServiceDistributor):
    def __init__(self, route: str, ratio: float, add_route):
        super().__init__(route)

        self._ratio = ratio
        self._add_route = add_route

        self._add_route_count = 0
        self._reqs_count = 0

    def get_route(self) -> str:
        if math.isclose(self._ratio, 1.0):
            return self._add_route
        elif math.isclose(self._ratio, 0.0):
            return self._route

        # to avoid overflow
        if self._reqs_count >= 1000_000_000:
            self._add_route_count, self._reqs_count = 0, 0

        if self._reqs_count == 0:
            current_ratio = math.inf
        else:
            current_ratio = self._add_route_count / self._reqs_count

        # to adjust the current ratio to the desired one
        if current_ratio > self._ratio:
            res = self._route
        else:
            self._add_route_count += 1
            res = self._add_route
        
        self._reqs_count += 1
        return res
