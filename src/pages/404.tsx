import React from "react"

import Layout from "../components/layout"
import SEO from "../components/seo"

const NotFoundPage: React.FC = () => (
  <Layout>
    <SEO title="Not found" />
    <h1>Not found</h1>
    <p>This path leads nowhere, get back!</p>
  </Layout>
)

export default NotFoundPage
