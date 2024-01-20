FROM node:latest
WORKDIR /app
COPY . ./
RUN npm install -g serve
CMD ["serve", "-s", "build", "-p", "8080"]