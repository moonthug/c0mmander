#
# Base Node
FROM mhart/alpine-node:12 AS base
RUN apk add --no-cache tini
WORKDIR /opt/app
ENTRYPOINT ["/sbin/tini", "--"]
COPY package*.json ./

#
# Dependencies
FROM base AS dependencies
RUN npm set progress=false
RUN npm install --only=production
RUN cp -R node_modules prod_node_modules
RUN npm ci

#
# Build
FROM base AS build
COPY --from=dependencies /opt/app/node_modules ./node_modules
COPY . .
RUN npm run build

#
# Test
#FROM dependencies AS test
#COPY . .
#RUN npm run lint && npm run test

#
# Release
FROM base AS release
COPY --from=dependencies /opt/app/prod_node_modules ./node_modules
COPY --from=build /opt/app/dist ./dist
EXPOSE 3000
CMD npm run start
