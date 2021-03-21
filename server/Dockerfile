FROM mhart/alpine-node:12

ARG ENVIRONMENT=ci
ENV NODE_ENV ${ENVIRONMENT}

WORKDIR /opt/app

COPY . .

RUN npm set progress=false
RUN npm install
RUN npm build

CMD ["npm", "start"]
