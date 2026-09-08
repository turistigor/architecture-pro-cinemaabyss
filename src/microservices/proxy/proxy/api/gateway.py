import httpx
from fastapi import Depends, HTTPException, Request, Response
from fastapi.routing import APIRouter
from loguru import logger

from proxy.routing import Distributor, get_distributor

movies_router = APIRouter(prefix='/api')


@movies_router.api_route('/{path:path}', methods = ('GET', 'POST'))
async def movies_handler(
    request: Request,
    distributor: Distributor = Depends(get_distributor)
) -> dict:
    logger.info(f'Request received: {request.url}')

    distributed_host = distributor.get_route(request.url.path)

    body = await request.body() if request.method == 'POST' else None

    headers = {}
    for name, value in request.headers.items():
        if name.lower() not in ["host", "content-length"]:
            headers[name] = value
    
    logger.info(f'Request sent to: {distributed_host}{request.url.path}')

    async with httpx.AsyncClient(base_url=distributed_host) as client:
        try:
            response = await client.request(
                method=request.method,
                url=request.url.path,
                headers=headers,
                content=body,
                params=request.query_params
            )
        except httpx.ConnectError:
            raise HTTPException(status_code=502, detail="Cannot connect to target host")
        except httpx.TimeoutException:
            raise HTTPException(status_code=504, detail="Target host timeout")
        except Exception as e:
            raise HTTPException(status_code=500, detail=f"Proxy error: {str(e)}")

    logger.success(f'Response received from: {response.url}')

    return Response(
        content=response.content,
        status_code=response.status_code,
        headers=dict(response.headers)
    )
