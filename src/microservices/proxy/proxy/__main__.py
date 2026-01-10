import asyncio as aio
from os import environ

import uvicorn
from fastapi import FastAPI

from proxy.api import health_router, movies_router


async def main():
    app = FastAPI()
    app.include_router(movies_router)
    app.include_router(health_router)

    host = environ.get('HOST', '0.0.0.0')
    port = int(environ.get('PORT', 8000))

    config = uvicorn.Config(app, host=host, port=port, log_level="info")
    server = uvicorn.Server(config)    

    await server.serve()


if __name__ == '__main__':
    aio.run(main())
