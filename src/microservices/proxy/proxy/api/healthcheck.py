from fastapi.routing import APIRouter

health_router = APIRouter()


@health_router.get("/health")
async def health_check() -> dict:
    return {"status": "OK"}
