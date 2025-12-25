FROM ghcr.io/astral-sh/uv:python3.12-bookworm-slim as proxy_builder

WORKDIR /opt/proxy/
COPY pyproject.toml uv.lock ./
RUN uv sync --frozen


FROM python:3.12-slim

WORKDIR /opt/proxy/
COPY --from=proxy_builder /opt/proxy/.venv/ .venv/
COPY proxy/ ./proxy

ENV PATH="/opt/proxy/.venv/bin:$PATH"
ENV PYTHONUNBUFFERED=1
ENV PYTHONDONTWRITEBYTECODE=1

RUN groupadd -r appuser && useradd -r -g appuser appuser
USER appuser

ENV PORT=8000
ENV HOST=0.0.0.0

EXPOSE 8000
RUN echo $(ls -la /opt/proxy/)
CMD python3 -m proxy
