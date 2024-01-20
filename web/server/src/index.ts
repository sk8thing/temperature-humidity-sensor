import express, { Express } from "express"
import cors from "cors"
import socket from "socket.io"
import http from "http"
import { sensorToServer, ServerToClient } from "./interfaces/events"
import {updateTemperature} from "./interfaces/requests";


const port: number = 8080
const app: Express = express()
const server: http.Server = http.createServer(app)
const io = new socket.Server<sensorToServer, ServerToClient>(server)

app.use(express.json())
app.use(cors({
    credentials: true,
    origin: ["https://example.com", "https://www.example.com"],
    methods: ["GET", "POST"]
}))

io.on("connection", (socket) => {
    socket.on("sensorUpdate", (api_key, temperature, humidity) => {
        if(api_key != process.env.API_KEY || !api_key) socket.disconnect()
        else socket.broadcast.emit("sensorUpdate", temperature, humidity)
    })
})

app.get("/", (_req, res) => {
    res.status(200).send()
})

app.post("/sensor", (req: updateTemperature<{api_key: string, temperature: number, humidity: number}>, res) => {
    console.log(JSON.stringify(req.body))
    if(!req.body.api_key || req.body.api_key != process.env.API_KEY || !req.body.temperature || !req.body.humidity) {
        res.status(400).send()
        return
    }
    io.emit("sensorUpdate", req.body.temperature, req.body.humidity);
    res.status(200).send()
})

app.get("*", (_req, res) => {
    res.status(404).send()
})

app.post("*", (_req, res) => {
    res.status(404).send()
})

server.listen(port)