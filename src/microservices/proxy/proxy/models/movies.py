from pydantic import BaseModel


class CreateMovieModel(BaseModel):
    title: str
    description: str
    genres: list[str]
    rating: float
