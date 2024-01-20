import { Request } from "express"
export interface updateTemperature<T> extends Request {
    body: T
}