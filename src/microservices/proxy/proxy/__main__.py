import asyncio as aio

import uvicorn
from fastapi import FastAPI

from proxy.api import health_router, movies_router


async def main():
    app = FastAPI()
    app.include_router(movies_router)
    app.include_router(health_router)

    config = uvicorn.Config(app, host='0.0.0.0', port=8000, log_level="info")
    server = uvicorn.Server(config)    

    await server.serve()


if __name__ == '__main__':
    aio.run(main())
